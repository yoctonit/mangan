//
// Created by Ivan on 03-Feb-23.
//

#ifndef OPENGL_EXAMPLES_SCENE_FILE_PARSER_H
#define OPENGL_EXAMPLES_SCENE_FILE_PARSER_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <json.h>
#include "Util.h"
#include "Camera.h"
#include "Square.h"
#include "Renderable.h"

using json = nlohmann::json;

class SceneFileParser {
public:
    explicit SceneFileParser(const std::string &file_path) {
//        std::ifstream file_stream(file_path, std::ios::in);
//        if (!file_stream.is_open()) {
//            std::cout << "SceneFileParser could not open " << file_path << "\n";
//        }
        std::string sceneDefinition = Mn::Util::Load(file_path);
        data = json::parse(sceneDefinition);
        // data = json::parse(file_stream);
    }

    std::shared_ptr<Camera> parseCamera() {
        std::shared_ptr<Camera> cam;
        auto camera = data["Camera"];
        if (camera != nullptr) {
            float centerX = camera["CenterX"].get<float>();
            float centerY = camera["CenterY"].get<float>();
            float width = camera["Width"].get<float>();
            std::vector<int> viewport = camera["Viewport"].get<std::vector<int>>();
            std::vector<float> bgColor = camera["BgColor"].get<std::vector<float>>();

            cam = std::make_shared<Camera>(
                    glm::vec2(centerX, centerY),
                    width,
                    glm::ivec4(viewport[0], viewport[1], viewport[2], viewport[3])
            );
            cam->setBackgroundColor(glm::vec4(bgColor[0], bgColor[1], bgColor[2], bgColor[3]));
        } else {
            std::cout << "No camera data\n";
        }
        return cam;
    }

    std::vector<std::shared_ptr<Renderable>> parseSquares(
            const std::shared_ptr<SimpleShader> &ss,
            const std::shared_ptr<Mn::VBO> &vbo) {
        std::vector<std::shared_ptr<Renderable>> sqSet;
        auto squares = data["Square"];
        if (squares == nullptr) {
            std::cout << "No squares data\n";
            return sqSet;
        }
        for (auto square: squares) {
            float posX = square["PosX"].get<float>();
            float posY = square["PosY"].get<float>();
            float width = square["Width"].get<float>();
            float height = square["Height"].get<float>();
            float rotation = square["Rotation"].get<float>();
            std::vector<float> color = square["Color"].get<std::vector<float>>();

            std::shared_ptr<Renderable> sq = std::make_shared<Renderable>(ss, vbo);
            sq->setColor(glm::vec4(color[0], color[1], color[2], color[3]));
            sq->getXform()->setPosition(posX, posY);
            sq->getXform()->setRotationInDegree(rotation);
            sq->getXform()->setSize(width, height);
            sqSet.push_back(sq);
        }
        return sqSet;
    }

private:
    json data{};
};

#endif //OPENGL_EXAMPLES_SCENE_FILE_PARSER_H
