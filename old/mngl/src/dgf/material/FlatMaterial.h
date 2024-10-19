//
// Created by Ivan on 20-Jan-23.
//

#ifndef OPENGL_EXAMPLES_FLATMATERIAL_H
#define OPENGL_EXAMPLES_FLATMATERIAL_H

package material;
import math.Vector;
import core.Texture;
public class FlatMaterial extends Material
{
public FlatMaterial(Texture texture)
{
super(
"./src/material/FlatMaterial.vert",
"./src/material/FlatMaterial.frag" );
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
locateUniforms();
addRenderSetting( "doubleSide", true );
addRenderSetting( "wireframe", false );
addRenderSetting( "lineWidth", 1 );}
};

#endif //OPENGL_EXAMPLES_FLATMATERIAL_H
