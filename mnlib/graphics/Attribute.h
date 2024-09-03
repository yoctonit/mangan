#ifndef INCLUDED_MN_GRAPHICS_ATTRIBUTE_H
#define INCLUDED_MN_GRAPHICS_ATTRIBUTE_H


namespace Mn {

    class Attribute {
    public:
        enum class DataType {
            Int, Float, Vec2, Vec3, Vec4
        };

        Attribute();

        Attribute(int location, DataType type);

        void Create(int location, DataType type);

        [[nodiscard]] int Location() const;

    private:
        int mLocation{};
        DataType mType{};
    };

}

#endif //INCLUDED_MN_GRAPHICS_ATTRIBUTE_H
