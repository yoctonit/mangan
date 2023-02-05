//
// Created by Ivan on 20-Jan-23.
//

#ifndef OPENGL_EXAMPLES_LIGHT_H
#define OPENGL_EXAMPLES_LIGHT_H

package light;
import core.Object3D;
import math.Vector;
public class Light extends Object3D
{
public static int AMBIENT = 1;
public static int DIRECTIONAL = 2;
public static int POINT = 3;
public int lightType;
public Vector color;
public Vector attenuation;
public Light()
{
    lightType = 0;
    color = new Vector(1, 1, 1);
    attenuation = new Vector(1, 0, 0);
}
};

#endif //OPENGL_EXAMPLES_LIGHT_H
