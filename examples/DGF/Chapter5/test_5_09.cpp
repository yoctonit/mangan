#include "core/Base.h"
#include "core/Object3D.h"
#include "core/Camera.h"
#include "core/Renderer.h"
#include "core/Mesh.h"
#include "geometry/BoxGeometry.h"
#include "geometry/RectangleGeometry.h"
#include "material/SpriteMaterial.h"
#include "extras/MovementRig.h"
#include "extras/GridHelper.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/transform.hpp"


class Test_5_09 : public Base {
public:
    void initialize() override {
        m_renderer = std::make_shared<Renderer>();

        m_scene = std::make_shared<Object3D>("scene");

        m_camera = std::make_shared<Camera>();
        m_camera->setPosition(glm::vec3(0.0f, 1.5f, 5.0f));

        m_rig = std::make_shared<MovementRig>();
        m_rig->attach(m_camera);
        m_scene->add(m_rig);

        std::shared_ptr<Geometry> geometry = std::make_shared<RectangleGeometry>();

        Texture ball("images/rolling-ball.png");
        auto material = std::make_shared<SpriteMaterial>(ball);
        material->uniforms()["billboard"].data().m_dataBool = true;
        material->uniforms()["tileCount"].data().m_dataVec2 = glm::vec2(4.0f, 4.0f);
        material->uniforms()["tileNumber"].data().m_dataFloat = 0.0f;

        m_sprite = std::make_shared<Mesh>("box", geometry, material);
        // box->setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
        m_sprite->applyMatrix(glm::translate(glm::vec3(0.0f, 0.5f, 0.0f)), true);
        m_scene->add(m_sprite);

        auto grid = std::make_shared<GridHelper>(
                10.0f, 10.0f,
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(1.0f, 0.5f, 0.5f),
                2);
        grid->rotateX(-3.14f / 2.0f, true);
        m_scene->add(grid);
    }

    void update() override {
        // note: looking at camera is similar to but
        // not precisely same effect as billboarding
        int tilesPerSecond = 8;
        auto tileNumber = (float) std::floor(m_timeSeconds * tilesPerSecond);
        m_sprite->material()->uniforms()["tileNumber"].data().m_dataFloat = tileNumber;

        m_rig->update(m_input, m_deltaTimeSeconds);
        m_renderer->render(m_scene, m_camera);
    }

private:
    std::shared_ptr<Renderer> m_renderer{};
    std::shared_ptr<Object3D> m_scene{};
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<MovementRig> m_rig;
    std::shared_ptr<Mesh> m_sprite;
};

int main() {
    Test_5_09().run();
    return 0;
}
