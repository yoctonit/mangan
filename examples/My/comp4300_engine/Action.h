#ifndef INCLUDED_MN_ACTION_H
#define INCLUDED_MN_ACTION_H

#include <string>

#include "vec2.h"


namespace Mn {

    class Action {
        std::string m_name;
        std::string m_type;
        vec2 m_pos = vec2(0.0f, 0.0f);

    public:
        Action();

        Action(std::string name, std::string type);

        Action(std::string name, vec2 pos);

        Action(std::string name, std::string type, vec2 pos);

        [[nodiscard]] const std::string &name() const;

        [[nodiscard]] const std::string &type() const;

        [[nodiscard]] const vec2 &pos() const;

        [[nodiscard]] std::string toString() const;
    };

}

#endif //INCLUDED_MN_ACTION_H
