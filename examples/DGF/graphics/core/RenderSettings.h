#ifndef DGF_GRAPHICS_CORE_RENDER_SETTINGS_H
#define DGF_GRAPHICS_CORE_RENDER_SETTINGS_H

class RenderSettings {
public:
    enum class Type {
        PointSize, LineWidth, DoubleSide, Wireframe /*,RoundedPoints*/
    };

    void apply();

    [[nodiscard]] bool isActive(Type type) const;

    void Activate(Type type);

    void Deactivate(Type type);

    void set(Type type, float value);

    void set(Type type, bool value);

    // for boolean settings (doubleSide and wireframe) returns 0.0f or 1.0f
    [[nodiscard]] float getValue(Type type) const;

private:
    float m_pointSize{1.0f};
    float m_lineWidth{1.0f};
    bool m_doubleSide{false};
    bool m_wireframe{false};
    // bool m_roundedPoints;

    bool m_activePointSize{false};
    bool m_activeLineWidth{false};
    bool m_activeDoubleSide{false};
    bool m_activeWireframe{false};
    // bool m_activeRoundedPoints{false};

    void applyPointSize() const;

    void applyLineWidth() const;

    void applyDoubleSide() const;

    void applyWireframe() const;
};

#endif //DGF_GRAPHICS_CORE_RENDER_SETTINGS_H
