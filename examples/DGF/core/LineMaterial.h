//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_LINEMATERIAL_H
#define OPENGL_EXAMPLES_LINEMATERIAL_H

package material;
import static org.lwjgl.opengl.GL40.*;
public class LineMaterial extends BasicMaterial
{
public LineMaterial()
{
    drawStyle = GL_LINES;
    addRenderSetting( "lineWidth", 1 );
}
public LineMaterial(String lineStyle)
{
if (lineStyle.equals("segments"))
drawStyle = GL_LINES;
else if (lineStyle.equals("connected"))
drawStyle = GL_LINE_STRIP;
else if (lineStyle.equals("loop"))
drawStyle = GL_LINE_LOOP;
else
{
System.out.println("Unknown line style: "
+ lineStyle);
drawStyle = GL_LINES;
}
addRenderSetting( "lineWidth", 1 );
}
}

#endif //OPENGL_EXAMPLES_LINEMATERIAL_H
