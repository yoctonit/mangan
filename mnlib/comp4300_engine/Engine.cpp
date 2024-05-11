#include <iostream>
#include <string>
//#include <utility>

#include "Engine.h"


namespace Mn {

    Engine::Config::Config(int w, int h, std::string t)
            : width{w}, height{h}, title{std::move(t)} {}

    Engine::Engine(const Config &config)
            : window_{config.width, config.height, config.title}, input_{Mn::Window::GetInput()} {
        std::cout << "Engine Constructor\n";
        window_.Create();
    }

    Engine::~Engine() {
        std::cout << "Engine Destructor\n";
    }

    Engine &Engine::SetScene(std::shared_ptr<Scene> scene) {
        scene_ = std::move(scene);
        return *this;
    }

    void Engine::Run() {
        if (scene_ == nullptr) {
            std::cerr << "Scene not set\n";
            return;
        };

        while (window_.IsOpen() && scene_->IsRunning()) {
            // auto st = glfwGetTime();
            // std::cout << "start time: " << st << "; ";
            InputSystem();


            scene_->Update();
            scene_->Render();

            // auto et = glfwGetTime();
            // std::cout << "end time: " << et << ": " << (et - st) * 1000.0 << "ms\n";
            window_.Display();

            // et = glfwGetTime();
            // std::cout << "after display: " << et << ": " << (et - st) * 1000.0 << "ms\n";
        }
    }

    //        input_.Update();
//        auto events = input_.Events();
//        std::cout << "Number of events in the queue: " << input_.EventsNumber() << std::endl;
//
//        for (int i = 0; i < input_.EventsNumber(); ++i) {
//            std::string type = "unknown";
//            if (events[i].type == GLFW_PRESS) type = "pressed ";
//            if (events[i].type == GLFW_RELEASE) type = "released ";
//
//
//            std::cout << type << events[i].key_code << std::endl;
//        }
    //input_.ResetEvents();

    void Engine::InputSystem() {
        Window::PollEvents();

        Mn::Event event{};
        while (input_.GetEvent(event)) {
            std::string type = "unknown";
            if (event.type == MN_PRESS) type = "pressed ";
            if (event.type == MN_RELEASE) type = "released ";
            std::cout << type << event.key << std::endl;

//            if (event.key == MN_KEY_ESCAPE && event.type == MN_PRESS) {
//                window_.Close();
//            }

            if (event.type == MN_PRESS || event.type == MN_RELEASE) {
                // if the current scene does not have an action associated with this key, skip the event
                // if (!scene_->HasAction(event.key)) {
                if (scene_->getActionMap().find(event.key) == scene_->getActionMap().end()) {
                    continue;
                }

                // determine start or end action by whether it was key press or release
                const std::string actionType = (event.type == MN_PRESS) ? "START" : "END";

                // look up the action and send the action to the scene
                scene_->DoAction(Action(scene_->getActionMap().at(event.key), actionType));
            }
        }

//        sf::Event event{};
//        while (m_window.pollEvent(event)) {
//
//            if (event.type == sf::Event::Closed) {
//                quit();
//            }
//
//            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
//                // if the current scene does not have an action associated with this key, skip the event
//                if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) {
//                    continue;
//                }
//
//                // determine start or end action by whether it was key press or release
//                const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
//
//                // look up the action and send the action to the scene
//                currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
//            }
//
//            // mouse event below
//            auto mousePos = sf::Mouse::getPosition(m_window);
//            vec2 pos = vec2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
//            if (event.type == sf::Event::MouseButtonPressed) {
//                switch (event.mouseButton.button) {
//                    case sf::Mouse::Left:
//                        currentScene()->doAction(Action("LEFT_CLICK", "START", pos));
//                        break;
//                    case sf::Mouse::Middle:
//                        currentScene()->doAction(Action("MIDDLE_CLICK", "START", pos));
//                        break;
//                    case sf::Mouse::Right:
//                        currentScene()->doAction(Action("RIGHT_CLICK", "START", pos));
//                        break;
//                    default:
//                        break;
//                }
//            }
//
//            if (event.type == sf::Event::MouseButtonReleased) {
//                switch (event.mouseButton.button) {
//                    case sf::Mouse::Left:
//                        currentScene()->doAction(Action("LEFT_CLICK", "END", pos));
//                        break;
//                    case sf::Mouse::Middle:
//                        currentScene()->doAction(Action("MIDDLE_CLICK", "END", pos));
//                        break;
//                    case sf::Mouse::Right:
//                        currentScene()->doAction(Action("RIGHT_CLICK", "END", pos));
//                        break;
//                    default:
//                        break;
//                }
//            }
//
//            if (event.type == sf::Event::MouseMoved) {
//                currentScene()->doAction(Action("MOUSE_MOVE", vec2(static_cast<float>(event.mouseMove.x),
//                                                                   static_cast<float>(event.mouseMove.y))));
//            }
//        }
    }

}