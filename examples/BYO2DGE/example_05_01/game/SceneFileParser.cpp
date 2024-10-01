#include "SceneFileParser.h"
#include <iostream>
#include <fstream>


SceneFileParser::SceneFileParser(const std::string &filePath) {
    std::string sceneDefinition = LoadFile(filePath);
    mData = json::parse(sceneDefinition);
}

Camera SceneFileParser::parseCamera() {
    Camera cam;
    auto camera = mData["Camera"];
    if (camera != nullptr) {
        float centerX = camera["CenterX"].get<float>();
        float centerY = camera["CenterY"].get<float>();
        float width = camera["Width"].get<float>();
        std::vector<int> viewport = camera["Viewport"].get<std::vector<int>>();
        std::vector<float> bgColor = camera["BgColor"].get<std::vector<float>>();

        cam = Camera(
                glm::vec2(centerX, centerY),
                width,
                glm::ivec4(viewport[0], viewport[1], viewport[2], viewport[3])
        );
        cam.setBackgroundColor({bgColor[0], bgColor[1], bgColor[2], bgColor[3]});
    } else {
        std::cerr << "SceneFileParser: no camera data\n";
    }
    return cam;
}

std::vector<Renderable> SceneFileParser::parseSquares(const Core &engine) {
    std::vector<Renderable> sqSet;

    auto squares = mData["Square"];
    if (squares == nullptr) {
        std::cerr << "SceneFileParser: no squares data\n";
        return sqSet;
    }

    for (auto square: squares) {
        float posX = square["PosX"].get<float>();
        float posY = square["PosY"].get<float>();
        float width = square["Width"].get<float>();
        float height = square["Height"].get<float>();
        float rotation = square["Rotation"].get<float>();
        std::vector<float> color = square["Color"].get<std::vector<float>>();

        Renderable sq = engine.createRenderable();
        sq.setColor({color[0], color[1], color[2], color[3]});
        sq.getXform().setPosition(posX, posY);
        sq.getXform().setRotationInDegree(rotation);
        sq.getXform().setSize(width, height);
        sqSet.push_back(sq);
    }
    return sqSet;
}

std::vector<TextureRenderable> SceneFileParser::parseTexturedSquares(const Core &engine) {
    std::vector<TextureRenderable> sqSet;

    auto squares = mData["TextureSquare"];
    if (squares == nullptr) {
        std::cerr << "SceneFileParser: no texture squares data\n";
        return sqSet;
    }

    for (auto square: squares) {
        float posX = square["PosX"].get<float>();
        float posY = square["PosY"].get<float>();
        float width = square["Width"].get<float>();
        float height = square["Height"].get<float>();
        float rotation = square["Rotation"].get<float>();
        std::vector<float> color = square["Color"].get<std::vector<float>>();
        std::string assetFile = square["file"].get<std::string>();

        TextureRenderable sq = engine.createTextureRenderable(Mn::Texture(assetFile));
        sq.setColor({color[0], color[1], color[2], color[3]});
        sq.getXform().setPosition(posX, posY);
        sq.getXform().setRotationInDegree(rotation);
        sq.getXform().setSize(width, height);
        sqSet.push_back(sq);
    }
    return sqSet;
}

std::string SceneFileParser::LoadFile(const std::string &fileName) {
    std::ifstream fileStream(fileName, std::ios::in);
    if (!fileStream.is_open()) {
        std::cerr << "Could not open " << fileName << "\n";
        return ""; // throw exception?
    }

    std::stringstream str;
    str << fileStream.rdbuf();

    fileStream.close();
    return str.str();
}
