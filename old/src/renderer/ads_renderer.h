//
// Created by ivan on 4.5.2020..
//

#ifndef INCLUDED_ADS_RENDERER_H
#define INCLUDED_ADS_RENDERER_H

#include "glad/glad.h"
#include "core/shader/shader_program.h"
#include "camera/perspective_camera.h"
#include "model/model.h"
#include "light/point_light.h"

#include <string>
#include <vector>

namespace mn {

    class ads_renderer {

    public:
        static ads_renderer& instance();

        void add(model* m);

        void initialize();
        void render(const mn::perspective_camera& camera, const point_light& light) const;

    private:
        ads_renderer() : program(nullptr) {}
        ~ads_renderer() = default;
        ads_renderer(const ads_renderer&) = default;
        const ads_renderer& operator=(const ads_renderer& renderer) const {
            if (this == &renderer) return *this; // self-assignment check
            return *this; // return *this anyway, because it's a singleton
        }

        shader_program*  program;
        std::vector<std::pair<model*, GLuint>> _objects;
    };

}

#endif //INCLUDED_ADS_RENDERER_H
