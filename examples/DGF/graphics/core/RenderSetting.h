#ifndef DGF_GRAPHICS_CORE_RENDER_SETTING_H
#define DGF_GRAPHICS_CORE_RENDER_SETTING_H

class RenderSetting {
public:
    virtual void apply() = 0;
};

class RenderSettingPointSize : public RenderSetting {
public:
    explicit RenderSettingPointSize(int pointSize);

    void apply() override;

private:
    int m_pointSize{1};
};

/*
class RenderSettingRoundedPoints : public RenderSetting {
public:
    explicit RenderSettingRoundedPoints(bool roundedPoints);
    virtual void apply() override;
private:
    bool m_roundedPoints{};
};
*/

class RenderSettingLineWidth : public RenderSetting {
public:
    explicit RenderSettingLineWidth(int lineWidth);

    void apply() override;

private:
    int m_lineWidth{1};
};

class RenderSettingDoubleSide : public RenderSetting {
public:
    explicit RenderSettingDoubleSide(bool doubleSide);

    void apply() override;

private:
    bool m_doubleSide{};
};

class RenderSettingWireframe : public RenderSetting {
public:
    explicit RenderSettingWireframe(bool wireframe);

    void apply() override;

private:
    bool m_wireframe{};
};

#endif //DGF_GRAPHICS_CORE_RENDER_SETTING_H
