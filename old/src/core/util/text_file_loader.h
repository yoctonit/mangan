//
// Created by ivan on 22.4.2020..
//

#ifndef INCLUDED_TEXT_FILE_LOADER_H
#define INCLUDED_TEXT_FILE_LOADER_H

#include <string>

namespace mn {

    class text_file_loader {

    public:
        static bool load(const std::string &file_path);

        [[nodiscard]] static const std::string& get_contents() { return _contents; }

    private:
        static std::string _contents;
    };

}

#endif //INCLUDED_TEXT_FILE_LOADER_H
