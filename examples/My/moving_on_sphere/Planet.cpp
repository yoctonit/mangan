#include <glm/gtc/matrix_transform.hpp>
#include "Planet.h"
#include "geometry/Icosahedron.h"
#include "geometry/Sphere.h"

Planet::Planet(float radius)
        : mShaderLoader{"shader/ads.vs.glsl", "shader/ads.fs.glsl"},
          mVao{}, mBuffer{} {

    Mn::Icosahedron model(radius);
//    Mn::Sphere model(radius);
    mBuffer = Mn::Vbo(model.Data(Mn::Geometry::Type::PositionsAndNormals));
    mVertexCount = model.VertexCount();

    mVao.Connect(mBuffer, 0, 3, 6, 0);
    mVao.Connect(mBuffer, 1, 3, 6, 3);
}

void Planet::Draw(const Camera &camera, const point_light &light) const {
    glm::mat4 v = camera.ViewMatrix();
    glm::mat4 p = camera.ProjectionMatrix();

//    glm::mat4 m = glm::translate(glm::mat4{1.0f}, glm::vec3{0.0f, 0.0f, 0.0f});
    glm::mat4 m = glm::mat4{1.0f};
    glm::mat4 mv = v * m;
    glm::mat4 mvp = p * mv;

    glm::mat3 n = glm::transpose(glm::inverse(glm::mat3(mv)));

    glm::vec4 light_position = v * light.position(); // Light position in eye coords.
    glm::vec3 Ka(glm::vec3(0.5f, 0.0f, 0.0f)); // Ambient reflectivity
    glm::vec3 Kd(glm::vec3(0.5f, 0.0f, 0.0f)); // Diffuse reflectivity
    glm::vec3 Ks(glm::vec3(0.8f, 0.8f, 0.8f)); // Specular reflectivity
    float shininess = 50.0f;

    mShaderLoader.Use();

    mShaderLoader.Set("u_light.position", light_position);
    mShaderLoader.Set("u_light.La", light.ambient());
    mShaderLoader.Set("u_light.Ld", light.diffuse());
    mShaderLoader.Set("u_light.Ls", light.specular());

    mShaderLoader.Set("u_material.Ka", Ka);
    mShaderLoader.Set("u_material.Kd", Kd);
    mShaderLoader.Set("u_material.Ks", Ks);
    mShaderLoader.Set("u_material.shininess", shininess);

    mShaderLoader.Set("viewPosition", camera.mPosition);

    mShaderLoader.Set("projectionMatrix", camera.ProjectionMatrix());
    mShaderLoader.Set("viewMatrix", camera.ViewMatrix());
    mShaderLoader.Set("modelMatrix", glm::mat4{1.0f});

    mVao.Draw(GL_TRIANGLES, 0, mVertexCount);
}
