#ifndef BYO2DGE_SCENE_FILE_PARSER_H
#define BYO2DGE_SCENE_FILE_PARSER_H

#include <string>
#include <vector>

#include "../../common/nlohmann/json.h"
#include "../src/Core.h"
#include "../src/Camera.h"
#include "../src/Renderable.h"

using json = nlohmann::json;

class SceneFileParser {
public:
    explicit SceneFileParser(const std::string &filePath);

    Camera parseCamera();

    std::vector<Renderable> parseSquares(const Core &engine);

private:
    json mData{};

    /*
     * Read contents of the file as string
     * @param [in] fileName - Path to the file
     * @param [out] - On successful read file contents, on failed read empty string;
     */
    static std::string LoadFile(const std::string &fileName);
};

#endif //BYO2DGE_SCENE_FILE_PARSER_H
