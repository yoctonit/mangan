#ifndef INCLUDED_MN_SCENE_H
#define INCLUDED_MN_SCENE_H

#include <memory>
#include <map>

#include "Action.h"
//#include "EntityManager.h"

namespace Mn {

    class Engine;

    typedef std::map<int, std::string> ActionMap;

    class Scene {
    protected:
        Engine *m_game = nullptr;
        // EntityManager m_entityManager;
        ActionMap m_actionMap;
        bool m_paused = false;
        bool m_isRunning = true;
        size_t m_currentFrame = 0;

        // virtual void onEnd() = 0;

        void setPaused(bool paused);

    public:

        Scene();

        explicit Scene(Engine *gameEngine);

        virtual ~Scene();

        virtual void Update() = 0;

        virtual void sDoAction(const Action &action) = 0;

        virtual void Render() const = 0;

        virtual void DoAction(const Action &action);

        void registerAction(int inputKey, const std::string &actionName);

        // [[nodiscard]] float width() const;

        // [[nodiscard]] float height() const;

        [[nodiscard]] size_t currentFrame() const;

        [[nodiscard]] bool IsRunning() const;

        [[nodiscard]] const ActionMap &getActionMap() const;
    };

}

#endif //INCLUDED_MN_SCENE_H
