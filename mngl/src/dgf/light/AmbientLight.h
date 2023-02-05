//
// Created by Ivan on 20-Jan-23.
//

#ifndef OPENGL_EXAMPLES_AMBIENTLIGHT_H
#define OPENGL_EXAMPLES_AMBIENTLIGHT_H

package light;
import math.Vector;
public class AmbientLight extends Light
{
public AmbientLight(Vector color)
{
lightType = Light.AMBIENT;
this.color = color;
}
}

#endif //OPENGL_EXAMPLES_AMBIENTLIGHT_H
