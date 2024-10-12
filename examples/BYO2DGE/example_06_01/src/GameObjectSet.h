#ifndef BYO2DGE_GAME_OBJECT_SET_H
#define BYO2DGE_GAME_OBJECT_SET_H

#include <string>
#include <unordered_map>
#include "engine/Input.h"
#include "Camera.h"
#include "GameObject.h"


template<typename T>
class GameObjectSet {
public:
//    GameObjectSet() = default;

    [[nodiscard]] int size() {
        return mSet.size();
    }

    T &getObject(const std::string &name) {
        return mSet[name];
    }

    void addToSet(const std::string &name, T gameObject) {
        mSet.insert({name, gameObject});
    }

    void removeFrom(const std::string &name) {
        mSet.erase(name);
    }

    void update(const Mn::Input &input) {
        for (auto &element: mSet) {
            element.second.update(input);
        }
    }

    virtual void draw(const Camera &camera) {
        for (auto &element: mSet) {
            element.second.draw(camera);
        }
    }

protected:
    std::unordered_map<std::string, T> mSet{};
};

#endif //BYO2DGE_GAME_OBJECT_SET_H
