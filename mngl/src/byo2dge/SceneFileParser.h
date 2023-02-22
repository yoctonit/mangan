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
#include "SquareGeometryBuffer.h"
#include "renderable/Renderable.h"
#include "renderable/TextureRenderable.h"

using json = nlohmann::json;

class SceneFileParser {
public:
    explicit SceneFileParser(const std::string &file_path) {
        std::string sceneDefinition = Mn::Util::Load(file_path);
        data = json::parse(sceneDefinition);
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
            const std::shared_ptr<ShaderInterface> &ss,
            const std::shared_ptr<SquareGeometryBuffer> &geometry) {
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

            std::shared_ptr<Renderable> sq = std::make_shared<Renderable>(ss, geometry);
            sq->setColor(glm::vec4(color[0], color[1], color[2], color[3]));
            sq->getXform()->setPosition(posX, posY);
            sq->getXform()->setRotationInDegree(rotation);
            sq->getXform()->setSize(width, height);
            sqSet.push_back(sq);
        }
        return sqSet;
    }

    std::vector<std::shared_ptr<Renderable>> parseTextureSquares(
            const std::shared_ptr<ShaderInterface> &ss,
            const std::shared_ptr<SquareGeometryBuffer> &geometry) {
        std::vector<std::shared_ptr<Renderable>> sqSet;
        auto squares = data["TextureSquare"];
        if (squares == nullptr) {
            std::cout << "No texture squares data\n";
            return sqSet;
        }
        for (auto square: squares) {
            float posX = square["PosX"].get<float>();
            float posY = square["PosY"].get<float>();
            float width = square["Width"].get<float>();
            float height = square["Height"].get<float>();
            float rotation = square["Rotation"].get<float>();
            std::string assetFile = square["file"].get<std::string>();
            std::vector<float> color = square["Color"].get<std::vector<float>>();

            std::shared_ptr<Mn::Texture> texture;
            if (ends_with(assetFile, ".jpg")) {
                texture = std::make_shared<Mn::Texture>(assetFile, GL_RGB);
            } else if (ends_with(assetFile, ".png")) {
                texture = std::make_shared<Mn::Texture>(assetFile, GL_RGBA);
            } else {
                std::cout << "Unsupported image file.\n";
            }
            std::shared_ptr<Renderable> sq = std::make_shared<TextureRenderable>(ss, geometry, texture);
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

    static inline bool ends_with(std::string const &value, std::string const &ending) {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }
};

#endif //OPENGL_EXAMPLES_SCENE_FILE_PARSER_H
