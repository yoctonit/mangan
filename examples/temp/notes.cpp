//
// Created by ivan on 26.4.2020..
//

//    std::vector<std::string> location::split_string(const std::string& str, const std::string& delimiter)
//    {
//        std::vector<std::string> strings;
//
//        std::string::size_type pos;
//        std::string::size_type prev = 0;
//        while ((pos = str.find(delimiter, prev)) != std::string::npos)
//        {
//            strings.push_back(str.substr(prev, pos - prev));
//            prev = pos + 1;
//        }
//
//        // To get the last substring (or only, if delimiter is not found)
//        strings.push_back(str.substr(prev));
//
//        return strings;
//    }
