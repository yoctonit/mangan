#include "Run.h"
#include "byo2dge/Engine.h"
#include "byo2dge/renderable/SpriteAnimateRenderable.h"
#include "byo2dge/renderable/FontRenderable.h"
#include "byo2dge/SceneFileParser.h"

class MyGame : public Level {
public:
    void initialize(int, int, std::shared_ptr<Engine> engine) override {
        mCamera = std::make_shared<Camera>(
                glm::vec2(50.0f, 33.0f), // center of the WC
                100.0f, // width of WC
                glm::ivec4(0, 0, 600, 400) // viewport:orgX, orgY, W, H
        );
        mCamera->setBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

        auto fontTexture = std::make_shared<Mn::Texture>("assets/consolas-72.png", GL_RGBA);
        auto minionSpriteTexture = std::make_shared<Mn::Texture>("assets/minion_sprite.png", GL_RGBA);

        auto fontSysTexture = std::make_shared<Mn::Texture>("assets/fonts/system_default_font.png", GL_RGBA);
        auto fontCon16Texture = std::make_shared<Mn::Texture>("assets/fonts/consolas-16.png", GL_RGBA);
        auto fontCon24Texture = std::make_shared<Mn::Texture>("assets/fonts/consolas-24.png", GL_RGBA);
        auto fontCon32Texture = std::make_shared<Mn::Texture>("assets/fonts/consolas-32.png", GL_RGBA);
        auto fontCon72Texture = std::make_shared<Mn::Texture>("assets/fonts/consolas-72.png", GL_RGBA);
        auto fontSeg96Texture = std::make_shared<Mn::Texture>("assets/fonts/segment7-96.png", GL_RGBA);

        mFontImage = std::make_shared<SpriteRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                fontTexture
        );
        mFontImage->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mFontImage->getXform()->setPosition(15.0f, 50.0f);
        mFontImage->getXform()->setSize(20.0f, 20.0f);

        mMinion = std::make_shared<SpriteAnimateRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mMinion->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mMinion->getXform()->setPosition(15.0f, 25.0f);
        mMinion->getXform()->setSize(24.0f, 19.2f);
        mMinion->setSpriteSequence(512,
                                   0,                     // first element pixel position: top-left 512 is top of image, 0 is left of image
                                   204, 164, // width x height in pixels
                                   5,                       // number of elements in this sequence
                                   0);                    // horizontal padding in between
        mMinion->setAnimationType(eAnimationType::eSwing);
        mMinion->setAnimationSpeed(15);

        mHero = std::make_shared<SpriteRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mHero->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mHero->getXform()->setPosition(35.0f, 50.0f);
        mHero->getXform()->setSize(12.0f, 18.0f);
        mHero->setElementPixelPositions(0.0f, 120.0f, 0.0f, 180.0f);

        // Create the fonts
        mFISys = parseFonts("assets/fonts/system_default_font.json");
        mTextSysFont = std::make_shared<FontRenderable>(
                "System Font: in Red",
                mFISys,
                std::make_shared<SpriteRenderable>(
                        engine->getSpriteShader(),
                        engine->getSquareGeometryBuffer(),
                        fontSysTexture
                ));
        mTextSysFont->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        mTextSysFont->getXform()->setPosition(50.0f, 60.0f);
        mTextSysFont->setTextHeight(3.0f);
        // _initText(this.mTextSysFont, 50, 60, [1, 0, 0, 1], 3);

        mFICon16 = parseFonts("assets/fonts/consolas-16.json");
        mTextCon16 = std::make_shared<FontRenderable>(
                "Consolas 16: in black", mFICon16,
                std::make_shared<SpriteRenderable>(
                        engine->getSpriteShader(),
                        engine->getSquareGeometryBuffer(),
                        fontCon16Texture
                ));
        mTextCon16->setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        mTextCon16->getXform()->setPosition(50.0f, 55.0f);
        mTextCon16->setTextHeight(2.0f);
        // this._initText(this.mTextCon16, 50, 55, [0, 0, 0, 1], 2);

        mFICon24 = parseFonts("assets/fonts/consolas-24.json");
        mTextCon24 = std::make_shared<FontRenderable>(
                "Consolas 24: in black", mFICon24,
                std::make_shared<SpriteRenderable>(
                        engine->getSpriteShader(),
                        engine->getSquareGeometryBuffer(),
                        fontCon24Texture
                ));
        mTextCon24->setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        mTextCon24->getXform()->setPosition(50.0f, 50.0f);
        mTextCon24->setTextHeight(3.0f);
        // this._initText(this.mTextCon24, 50, 50, [0, 0, 0, 1], 3);

        mFICon32 = parseFonts("assets/fonts/consolas-32.json");
        mTextCon32 = std::make_shared<FontRenderable>(
                "Consolas 32: in white", mFICon32,
                std::make_shared<SpriteRenderable>(
                        engine->getSpriteShader(),
                        engine->getSquareGeometryBuffer(),
                        fontCon32Texture
                ));
        mTextCon32->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        mTextCon32->getXform()->setPosition(40.0f, 40.0f);
        mTextCon32->setTextHeight(4.0f);
        // this._initText(this.mTextCon32, 40, 40, [1, 1, 1, 1], 4);

        mFICon72 = parseFonts("assets/fonts/consolas-72.json");
        mTextCon72 = std::make_shared<FontRenderable>(
                "Consolas 72: in blue", mFICon72,
                std::make_shared<SpriteRenderable>(
                        engine->getSpriteShader(),
                        engine->getSquareGeometryBuffer(),
                        fontCon72Texture
                ));
        mTextCon72->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        mTextCon72->getXform()->setPosition(30.0f, 30.0f);
        mTextCon72->setTextHeight(6.0f);
        // this._initText(this.mTextCon72, 30, 30, [0, 0, 1, 1], 6);

        mFISeg96 = parseFonts("assets/fonts/segment7-96.json");
        mTextSeg96 = std::make_shared<FontRenderable>(
                "Segment7-92", mFISeg96,
                std::make_shared<SpriteRenderable>(
                        engine->getSpriteShader(),
                        engine->getSquareGeometryBuffer(),
                        fontSeg96Texture
                ));
        mTextSeg96->setColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
        mTextSeg96->getXform()->setPosition(30.0f, 15.0f);
        mTextSeg96->setTextHeight(7.0f);
        // this._initText(this.mTextSeg96, 30, 15, [1, 1, 0, 1], 7);

        mTextToWork = mTextCon16;
    }

    void draw() const override {
        Engine::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);

        mCamera->setViewAndCameraMatrix();

        mHero->draw(*mCamera);
        mFontImage->draw(*mCamera);
        mMinion->draw(*mCamera);

        mTextSysFont->draw(*mCamera);
        mTextCon16->draw(*mCamera);
        mTextCon24->draw(*mCamera);
        mTextCon32->draw(*mCamera);
        mTextCon72->draw(*mCamera);
        mTextSeg96->draw(*mCamera);
    }

    void update(const Mn::Input &input, double) override {
        float deltaX = 0.05;
        std::shared_ptr<Transform> xform = mHero->getXform();

        if (input.is_pressed(Mn::key::right)) {
            xform->incXPosBy(deltaX);
            if (xform->getXPos() > 100.0f) // the right-bound of the window
                xform->setPosition(0.0f, 50.0f);
        }
        if (input.is_pressed(Mn::key::left)) {
            xform->incXPosBy(-deltaX);
            if (xform->getXPos() < 0.0f) // the right-bound of the window
                xform->setPosition(100.0f, 50.0f);
        }

        // New update code for changing the sub-texture regions being shown"
        float deltaT = 0.001;

        // The font image:
        // zoom into the texture by updating texture coordinate
        // For font: zoom to the upper left corner by changing bottom right
        std::vector<float> texCoord = mFontImage->getElementUVCoordinateArray();
        // The 8 elements:
        //      mTexRight,  mTexTop,          // x,y of top-right
        //      mTexLeft,   mTexTop,
        //      mTexRight,  mTexBottom,
        //      mTexLeft,   mTexBottom
        float b = texCoord[5] + deltaT; // eTexCoordArrayIndex.eBottom
        float r = texCoord[0] - deltaT; // eTexCoordArrayIndex.eRight
        if (b > 1.0) {
            b = 0;
        }
        if (r < 0) {
            r = 1.0;
        }
        mFontImage->setElementUVCoordinate(
                texCoord[2], // eTexCoordArrayIndex.eLeft
                r,
                b,
                texCoord[1] // eTexCoordArrayIndex.eTop
        );

        // remember to update the minion's animation
        mMinion->updateAnimation();

        // interactive control of the display size
        // choose which text to work on
        if (input.is_clicked(Mn::key::a)) {
            mTextToWork = mTextCon16;
        }
        if (input.is_clicked(Mn::key::s)) {
            mTextToWork = mTextCon24;
        }
        if (input.is_clicked(Mn::key::d)) {
            mTextToWork = mTextCon32;
        }
        if (input.is_clicked(Mn::key::q)) {
            mTextToWork = mTextCon72;
        }

        float deltaF = 0.005f;
        if (input.is_pressed(Mn::key::up)) {
            if (input.is_pressed(Mn::key::x)) {
                mTextToWork->getXform()->incWidthBy(deltaF);
            }
            if (input.is_pressed(Mn::key::z)) {
                mTextToWork->getXform()->incHeightBy(deltaF);
            }
            // mTextSysFont->setText(mTextToWork->getXform()->getWidth() + "x" + mTextToWork->getXform()->getHeight());
        }

        if (input.is_pressed(Mn::key::down)) {
            if (input.is_pressed(Mn::key::x)) {
                mTextToWork->getXform()->incWidthBy(-deltaF);
            }
            if (input.is_pressed(Mn::key::z)) {
                mTextToWork->getXform()->incHeightBy(-deltaF);
            }
            // mTextSysFont->setText(mTextToWork->getXform()->getWidth() + "x" + mTextToWork->getXform()->getHeight());
        }
    }

    void cleanup() {}

private:
// textures:
//    this.kFontImage = "assets/consolas-72.png";
//    this.kMinionSprite = "assets/minion_sprite.png";
//
//    // the fonts
//    this.kFontCon16 = "assets/fonts/consolas-16";  // notice font names do not need extensions!
//    this.kFontCon24 = "assets/fonts/consolas-24";
//    this.kFontCon32 = "assets/fonts/consolas-32";  // this is also the default system font
//    this.kFontCon72 = "assets/fonts/consolas-72";
//    this.kFontSeg96 = "assets/fonts/segment7-96";

    std::shared_ptr<Camera> mCamera;

    std::shared_ptr<Renderable> mHero;
    std::shared_ptr<Renderable> mFontImage;
    std::shared_ptr<Renderable> mMinion;

    FontInfo mFISys{};
    FontInfo mFICon16{};
    FontInfo mFICon24{};
    FontInfo mFICon32{};
    FontInfo mFICon72{};
    FontInfo mFISeg96{};
    std::shared_ptr<FontRenderable> mTextSysFont;
    std::shared_ptr<FontRenderable> mTextCon16;
    std::shared_ptr<FontRenderable> mTextCon24;
    std::shared_ptr<FontRenderable> mTextCon32;
    std::shared_ptr<FontRenderable> mTextCon72;
    std::shared_ptr<FontRenderable> mTextSeg96;

    std::shared_ptr<FontRenderable> mTextToWork;
};

int main() {
    Mn::Window window(640, 480, "ExampleScene");
    Game game;
    game.addLevel(std::make_shared<MyGame>());
    Mn::Run<Game>(game, window);
    return 0;
}
