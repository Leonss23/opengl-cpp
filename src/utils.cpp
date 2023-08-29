#include "utils.h"

std::string get_file_contents(const char* filename) {
    std::string filepath = "res/shaders/" + std::string(filename);
    std::ifstream in(filepath, std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
        }
    std::cerr << "couldn't find " << filename << std::endl;
    throw(errno);
    }
