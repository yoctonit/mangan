//
// Created by Ivan on 22-Feb-23.
//

#ifndef OPENGL_EXAMPLES_GAME_OBJECT_SET_H
#define OPENGL_EXAMPLES_GAME_OBJECT_SET_H

/*
 * utility class for a collection of GameObject
 */

#include <vector>
#include <algorithm>
#include "GameObject.h"

class GameObjectSet {
public:
    GameObjectSet() = default;

    int size() { return (int) mSet.size(); }

    std::shared_ptr<GameObject> getObjectAt(int index) {
        return mSet[index];
    }

    void addToSet(const std::shared_ptr<GameObject> &obj) {
        mSet.push_back(obj);
    }

    // Check this function
    void removeFromSet(const std::shared_ptr<GameObject> &obj) {
        auto index = find(mSet.begin(), mSet.end(), obj);
        if (index != mSet.end()) {
            mSet.erase(index);
        }
    }

    void update(const Mn::Input &input) {
        for (auto &i: mSet) {
            i->update(input);
        }
    }

    void draw(const Camera &aCamera) const {
        for (auto &i: mSet) {
            i->draw(aCamera);
        }
    }

private:
    std::vector<std::shared_ptr<GameObject>> mSet;
};

#endif //OPENGL_EXAMPLES_GAME_OBJECT_SET_H
