#ifndef INCLUDED_MN_GRAPHICS_ATTRIBUTE_H
#define INCLUDED_MN_GRAPHICS_ATTRIBUTE_H

#include <string>

namespace Mn {

    class Attribute {
    public:
        Attribute();

        Attribute(int location, int type);

        [[nodiscard]] int Location() const;

        void Debug(const std::string &msg) const;

    private:
        int mLocation{-1};
        int mType{-1};

        [[nodiscard]] std::string TypeName() const;
    };

}

#endif //INCLUDED_MN_GRAPHICS_ATTRIBUTE_H
