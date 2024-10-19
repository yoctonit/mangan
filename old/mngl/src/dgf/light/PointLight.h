//
// Created by Ivan on 20-Jan-23.
//

#ifndef OPENGL_EXAMPLES_POINTLIGHT_H
#define OPENGL_EXAMPLES_POINTLIGHT_H

package light;
import math.Vector;
public class PointLight extends Light
{
public PointLight(Vector color, Vector position,
        Vector attenuation)
{
lightType = Light.POINT;
this.color = color;
setPosition(position);
this.attenuation = attenuation;
}
// sets default attenuation coefficients
public PointLight(Vector color, Vector position)
{
this(color, position, new Vector(1, 0, 0.1));
}
};

#endif //OPENGL_EXAMPLES_POINTLIGHT_H
