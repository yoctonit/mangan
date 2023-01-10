//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_MATERIAL_H
#define OPENGL_EXAMPLES_MATERIAL_H

#include <glm/glm.hpp>
#include <map>
#include "openGLUtils.h"
#include "uniform.h"
#include "RenderSetting.h"

class Material {
public:
public int programRef;
public int drawStyle;
// Store Uniform objects,
// indexed by name of associated variable in shader.
public HashMap<String, Uniform> uniforms;
// Store OpenGL render settings,
// indexed by variable name.
// Additional settings added by extending classes.
public HashMap<String, RenderSetting> renderSettings;
public Material(String vertexShaderFileName,
                String fragmentShaderFileName)
    {
        programRef = OpenGLUtils.initFromFiles(
                vertexShaderFileName, fragmentShaderFileName );
        drawStyle = GL_TRIANGLES;
        uniforms = new HashMap<String, Uniform>();
// Each shader typically contains these uniforms;
// values set during render process from Mesh/Camera.
// Additional uniforms added by extending classes.
        addUniform("mat4", "modelMatrix", null);
        addUniform("mat4", "viewMatrix", null);
        addUniform("mat4", "projectionMatrix", null);
        renderSettings = new HashMap<String, RenderSetting>();
    }
public void addUniform(String dataType,
                       String variableName, Object data)
    {
        uniforms.put(variableName, new Uniform(dataType, data));
    }
// initialize all uniform variable references
public void locateUniforms()
    {
        for (String variableName : uniforms.keySet())
        {
            Uniform uniform = uniforms.get(variableName);
            uniform.locateVariable(programRef, variableName);
        }
    }
public void addRenderSetting(String settingName,
                             Object data)
    {
        renderSettings.put(settingName,
                           new RenderSetting(settingName, data));
    }
};

#endif //OPENGL_EXAMPLES_MATERIAL_H
