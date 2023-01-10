//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_SURFACEMATERIAL_H
#define OPENGL_EXAMPLES_SURFACEMATERIAL_H

package material;
import static org.lwjgl.opengl.GL40.*;
public class SurfaceMaterial extends BasicMaterial
{
public SurfaceMaterial()
{
    drawStyle = GL_TRIANGLES;
    addRenderSetting( "doubleSide", true );
    addRenderSetting( "wireframe", false );
    addRenderSetting( "lineWidth", 1 );
}
}

#endif //OPENGL_EXAMPLES_SURFACEMATERIAL_H
