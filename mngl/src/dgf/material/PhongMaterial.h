//
// Created by Ivan on 20-Jan-23.
//

#ifndef OPENGL_EXAMPLES_PhongMaterial_H
#define OPENGL_EXAMPLES_PhongMaterial_H

package material;
import math.Vector;
import core.Texture;
public class PhongMaterial extends Material
{
public PhongMaterial(Texture texture)
{
super(
"./src/material/PhongMaterial.vert",
"./src/material/PhongMaterial.frag" );
if (texture == null)
addUniform("bool", "useTexture", 0);
else
{
addUniform("bool", "useTexture", 1);
addUniform("sampler2D", "tex",
new Vector(texture.textureRef, 1));
}
addUniform( "vec3", "baseColor", new Vector(1,1,1) );
addUniform( "Light", "light0", null );
addUniform( "Light", "light1", null );
addUniform( "Light", "light2", null );
addUniform( "Light", "light3", null );
if (texture == null)
addUniform("bool", "useTexture", 0);
else
{
addUniform("bool", "useTexture", 1);
addUniform("sampler2D", "tex",
new Vector(texture.textureRef, 1));
}
addUniform("vec3", "viewPosition", new Vector(0,0,0) );
addUniform("float", "specularStrength", 1.0f);
addUniform("float", "shininess", 32.0f);
locateUniforms();
addRenderSetting( "doubleSide", true );
addRenderSetting( "wireframe", false );
addRenderSetting( "lineWidth", 1 );}
};

#endif //OPENGL_EXAMPLES_PhongMaterial_H
