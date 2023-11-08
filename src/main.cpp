#include <iostream>
#include <filesystem>
#include <future>
#include <vector>
#include "transpiler.h"

int main(int argc, char *argv[]) {
        std::vector<std::future<void>> futures;
        futures.reserve(argc - 1);
        for (int i = 1; i < argc; i++) {
                std::filesystem::path path(argv[i]);
                if (path.extension() != ".djs")
                        std::cout << "Invalid file: " << path << " (Expects .djs file)\n";
                
                auto foo = [](std::filesystem::path &&path) {
                        EasyJS::Transpiler t;
                        t.load_file(path.c_str());
                        std::string parsed_text = t.parse_loaded_file();
                        t.write_output(path.replace_extension(".js").c_str(), parsed_text.c_str());
                };
                
                
                futures.push_back(std::async(std::launch::async, foo, std::move(path)));
        }
        std::cout << futures.size() << "\n";
        for (auto& future : futures)
                future.get();
	return 0;
}