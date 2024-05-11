#include "Scene.h"
#include "Engine.h"


namespace Mn {
    Scene::Scene() = default;

    Scene::Scene(Mn::Engine *gameEngine) : m_game(gameEngine) {}

    Scene::~Scene() = default;

    void Scene::DoAction(const Action &action) {
        sDoAction(action);
    }

    void Scene::setPaused(bool paused) {
        m_paused = paused;
    }

    void Scene::registerAction(int inputKey, const std::string &actionName) {
        m_actionMap[inputKey] = actionName;
    }

//float Scene::width() const {
//    return static_cast<float>(m_game->window().getSize().x);
//}
//
//float Scene::height() const {
//    return static_cast<float>(m_game->window().getSize().y);
//}

    size_t Scene::currentFrame() const {
        return m_currentFrame;
    }

    bool Scene::IsRunning() const {
        return m_isRunning;
    }

    const ActionMap &Scene::getActionMap() const {
        return m_actionMap;
    }
}
