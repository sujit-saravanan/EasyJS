#include "transpiler.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <pugixml.hpp>
#include <format>

char EasyJS::Transpiler::current_character() {
        return m_file_content.at(m_current_index);
}
std::string& EasyJS::Transpiler::current_file_content()& noexcept {
        return m_file_content;
}
const std::string& EasyJS::Transpiler::current_file_content() const& noexcept {
        return m_file_content;
}

void EasyJS::Transpiler::load_file(const char* filepath) {
        FILE* file = fopen(filepath, "rb");
        if (file == nullptr) [[unlikely]] {
                std::cout << "Failed to open the file: " << filepath << "\n";
                std::exit(EXIT_FAILURE);
        }
        
        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        m_file_content.resize_and_overwrite(file_size, [&](char* buf, size_t n) {
                return fread(buf, 1, n, file);
        });
        
        if (ferror(file)) [[unlikely]] {
                std::cout << "Failed to read the file: " << filepath << "\n";
                std::exit(EXIT_FAILURE);
        }
        
        fclose(file);
}

std::string EasyJS::Transpiler::parse_loaded_file() {
        std::string parsed_file;
        static constexpr std::string_view pattern = "DomElement ";
        std::array<int32_t, 256> bad_chars{};
        bad_chars.fill(-1);
        
        for (int32_t i = 0; i < pattern.size(); i++)
                bad_chars[pattern[i]] = i;
        
        size_t start = 0;
        while (m_current_index <= (m_file_content.size() - pattern.size())) {
                int32_t comp = pattern.size() - 1;
                
                while (comp >= 0 && pattern[comp] == m_file_content[m_current_index + comp])
                        comp--;
                
                if (comp < 0) { // Found Match
                        parsed_file += std::string_view(m_file_content.begin() + start, m_file_content.begin() + m_current_index);
                        parsed_file += parse_djs();
                        start = m_current_index;
                        
                        if (m_current_index + pattern.size() < m_file_content.size())
                                m_current_index += pattern.size() - bad_chars[m_file_content[m_current_index + pattern.size()]];
                        else
                                m_current_index++;
                } else {
                        m_current_index += std::max(comp - bad_chars[m_file_content[m_current_index + comp]], 1);
                }
        }
        parsed_file += std::string_view(m_file_content.begin() + start, m_file_content.end());

        return parsed_file;
}
std::string EasyJS::Transpiler::parse_djs() {
        m_current_index += 11; // Skip "DomElement "
        std::string generated_function = "function ";
        generated_function += parse_djs_name();
        generated_function += parse_djs_parameters();
        generated_function += parse_djs_body();
        return generated_function;
}
void EasyJS::Transpiler::expect(char expected_character, std::string_view error_message) {
        if (current_character() != expected_character) {
                std::cout << std::format("ERROR: {} at ({},{})\n", error_message, current_line(), current_offset());
                std::exit(EXIT_FAILURE);
        }
}
std::string_view EasyJS::Transpiler::parse_djs_name() {
        size_t start = m_current_index;
        
        while (m_current_index < m_file_content.size() && !(current_character() == '(' || isblank(current_character())))
                m_current_index++;
        while (isblank(current_character()))
                m_current_index++;
        
        return {m_file_content.begin() + start, m_file_content.begin() + m_current_index};
}
std::string_view EasyJS::Transpiler::parse_djs_parameters() {
        expect('(', "Expected '('");
        size_t start = m_current_index;
        
        while (m_current_index < m_file_content.size() && current_character() != ')')
                m_current_index++;
        m_current_index++;
        
        while (isblank(current_character()))
                m_current_index++;
        
        return {m_file_content.begin() + start, m_file_content.begin() + m_current_index};
}

// trim from left
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
        s.erase(0, s.find_first_not_of(t));
        return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
        s.erase(s.find_last_not_of(t) + 1);
        return s;
}

struct simple_walker : pugi::xml_tree_walker {
        std::string output;
        
        std::string print_node(const pugi::xml_node& node) {
                std::string output = " <";
                output += node.name();
                for (const auto attr: node.attributes()) {
                        output += std::format(" {}=\"{}\"", attr.name(), attr.value());
                }
                output += ">";
                return output;
        }
        
        bool for_each(pugi::xml_node& node) override {
                std::string indent = std::string(depth() + 1, '\t');
                if (*node.value() != 0) {
                        std::string val = node.value();
                        ltrim(val);
                        rtrim(val);
                        output += std::format("{}// {}\n", indent, val);
                        std::string name = "_" + std::to_string(node.parent().hash_value());
                        output += std::format("{}{}.appendChild(document.createTextNode(`{}`));\n", indent, name, val);
                        return true;
                }
                
                std::string name = "_" + std::to_string(node.hash_value());
                
                output += std::format("{}//{}\n", indent, print_node(node));
                output += std::format("{}const {} = document.createElement(`{}`);\n", indent, name, node.name());
                
                for (const auto attr: node.attributes())
                        output += std::format("{}{}.setAttribute(`{}`, `{}`);\n", indent, name, attr.name(), attr.value());
                
                if (depth() > 0) {
                        std::string parent_name = "_" + std::to_string(node.parent().hash_value());
                        output += std::format("{}{}.appendChild({});\n", indent, parent_name, name);
                }
                
                return true; // continue traversal
        }
};

std::string EasyJS::Transpiler::parse_djs_body() {
        expect('{', "Expected '{'");
        int32_t curly_depth = 0;
        size_t start = m_current_index;
        
        while (m_current_index < m_file_content.size()) {
                if (current_character() == '{')
                        curly_depth++;
                if (current_character() == '}')
                        curly_depth--;
                if (curly_depth == 0)
                        break;
                m_current_index++;
        }
        m_current_index++;
        
        while (isblank(current_character()))
                m_current_index++;
        
        pugi::xml_document doc;
        doc.load_buffer_inplace((void*) (m_file_content.c_str() + start), m_current_index - start);
        
        
        simple_walker walker;
        walker.output += "{\n\tconst frag = document.createDocumentFragment();\n";
        doc.traverse(walker);
        for (const auto& node: doc.children()) {
                std::string name = "_" + std::to_string(node.hash_value());
                walker.output += std::format("\tfrag.appendChild({});\n",name);
        }
        walker.output += "\treturn frag;\n}";
        
        
        return std::move(walker.output);
}
size_t EasyJS::Transpiler::current_line() {
        size_t line_number = 1;
        for (size_t i = 0; i < m_current_index; i++)
                if (m_file_content[i] == '\n')
                        line_number++;
        return line_number;
}
size_t EasyJS::Transpiler::current_offset() {
        size_t offset = 1;
        for (size_t i = m_current_index; m_file_content[i] != '\n' && i > 0; i--)
                offset++;
        return offset;
}
void EasyJS::Transpiler::write_output(const char* filepath, const char* output) {
        FILE* file = fopen(filepath, "w");
        if (file == nullptr) [[unlikely]] {
                std::cout << "Failed to open the file: " << filepath << "\n";
                std::exit(EXIT_FAILURE);
        }
        
        fprintf(file, "%s\n", output);
        
        fclose(file);
}
