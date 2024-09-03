#include "Attribute.h"

namespace Mn {
    Attribute::Attribute() = default;

    Attribute::Attribute(int location, DataType type) {
        mLocation = location;
        mType = type;
    }

    void Attribute::Create(int location, Mn::Attribute::DataType type) {
        mLocation = location;
        mType = type;
    }

    int Attribute::Location() const {
        return mLocation;
    }

}