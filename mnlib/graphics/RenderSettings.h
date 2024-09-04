#ifndef INCLUDED_MN_GRAPHICS_RENDER_SETTINGS_H
#define INCLUDED_MN_GRAPHICS_RENDER_SETTINGS_H

namespace Mn {

    class RenderSettings {
    public:
        enum class Type {
            PointSize, LineWidth, DoubleSide, Wireframe /*,RoundedPoints*/
        };

        void Apply() const;

        void Set(Type type, bool value);

        void Set(Type type, float value);

        // for boolean settings (doubleSide and wireframe) returns 0.0f or 1.0f
        // [[nodiscard]] float Value(Type type) const;

    private:
        float mPointSize{1.0f};
        float mLineWidth{1.0f};
        bool mDoubleSide{false};
        bool mWireframe{false};

        void ApplyPointSize() const;

        void ApplyLineWidth() const;

        void ApplyDoubleSide() const;

        void ApplyWireframe() const;
    };

}

#endif //INCLUDED_MN_GRAPHICS_RENDER_SETTINGS_H
