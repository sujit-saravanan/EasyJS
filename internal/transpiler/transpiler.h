#pragma once
#include <string>

namespace EasyJS {
        class Transpiler {
        public: // Static Data
        public: // Public Constructors/Destructors/Overloads
        public: // Public Member Functions
                void load_file(const char* filepath);
                std::string parse_loaded_file();
                
                char current_character();
                
                size_t current_line();
                size_t current_offset();
                
                std::string& current_file_content()& noexcept;
                [[nodiscard]] const std::string& current_file_content() const& noexcept;
                
                void write_output(const char* filepath, const char* output);
        public: // Public Member Variables
        private: // Private Member Functions
                void expect(char expected_character, std::string_view error_message);
                
                std::string parse_djs();
                std::string_view parse_djs_name();
                std::string_view parse_djs_parameters();
                std::string parse_djs_body();
                
        private: // Private Member Variables
                std::string m_file_content;
                size_t m_current_index{0};
        };
}
