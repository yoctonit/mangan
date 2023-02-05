//
// Created by Ivan on 20-Jan-23.
//

#ifndef OPENGL_EXAMPLES_DIRECTIONALLIGHT_H
#define OPENGL_EXAMPLES_DIRECTIONALLIGHT_H

package light;
import math.Vector;
public class DirectionalLight extends Light
{
public DirectionalLight(Vector color, Vector direction)
{
lightType = Light.DIRECTIONAL;
this.color = color;
setDirection(direction);
}
};

#endif //OPENGL_EXAMPLES_DIRECTIONALLIGHT_H
