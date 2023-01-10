//
// Created by ivan on 22.4.2020..
//

#include "text_file_loader.h"
#include <fstream>
#include <sstream>

namespace mn {

    // define static members
    std::string text_file_loader::_contents{};

    /*
     * Read contents of the file as string
     * @param [in] file_path - Path to the file
     * @param [out] - true - successful read, false failed read;
     * If successful _contents member variable contains file contents,
     * else it contains empty string
     */
    bool text_file_loader::load(const std::string &file_path) {

        std::ifstream file_stream(file_path, std::ios::in);

        if(!file_stream.is_open()) {
            _contents.erase();
            return false;
        }

        std::stringstream str;
        str << file_stream.rdbuf();
        _contents = str.str();

        file_stream.close();
        return true;
    }

}
