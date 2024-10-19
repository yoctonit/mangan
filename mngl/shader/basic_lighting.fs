#version 430 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;

uniform vec3 uViewPosition;
uniform Material uMaterial;
uniform Light uLight;

out vec4 FragColor;

void main()
{
    // ambient
    vec3 ambient = uLight.ambient * uMaterial.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 uLightDir = normalize(uLight.position - FragPos);
    float diff = max(dot(norm, uLightDir), 0.0);
    vec3 diffuse = uLight.diffuse * (diff * uMaterial.diffuse);

    // specular
    vec3 viewDir = normalize(uViewPosition - FragPos);
    vec3 reflectDir = reflect(-uLightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = uLight.specular * (spec * uMaterial.specular);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
