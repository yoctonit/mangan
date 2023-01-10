//
// Created by ivan on 28.12.2022..
//

#ifndef INCLUDED_MN_UTIL_H
#define INCLUDED_MN_UTIL_H

#include <string>

namespace Mn::Util {

    std::string Load(const std::string &file_path);
//    class text_file_loader {
//
//public:
//    static bool load(const std::string &file_path);
//
//    [[nodiscard]] static const std::string& get_contents() { return _contents; }
//
//private:
//    static std::string _contents;
};

#endif //INCLUDED_MN_UTIL_H
