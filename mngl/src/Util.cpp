//
// Created by ivan on 28.12.2022..
//

#include "Util.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Mn::Util {

    /*
     * Read contents of the file as string
     * @param [in] file_path - Path to the file
     * @param [out] - On successful read file contents, on failed read empty string;
     */
    std::string Load(const std::string &file_path) {
        std::ifstream file_stream(file_path, std::ios::in);
        if (!file_stream.is_open()) {
            std::cout << "Could not open " << file_path << "\n";
            return ""; // throw exception?
        }

        std::stringstream str;
        str << file_stream.rdbuf();

        file_stream.close();
        return str.str();
    }

};
