//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_POINTMATERIAL_H
#define OPENGL_EXAMPLES_POINTMATERIAL_H
package material;
import static org.lwjgl.opengl.GL40.*;
public class PointMaterial extends BasicMaterial
{
public PointMaterial()
{
    drawStyle = GL_POINTS;
    addRenderSetting( "pointSize", 16 );
    addRenderSetting( "roundedPoints", true );
}
}
#endif //OPENGL_EXAMPLES_POINTMATERIAL_H
