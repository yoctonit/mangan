#version 430

#define NUM_STEPS 100

#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif
precision mediump int;

subroutine vec3 fractalType( vec2 tex_coord);
subroutine uniform fractalType fractal;
uniform vec2 u_julia_c;

uniform vec2 u_canvas_size;
uniform vec2 u_offset;
uniform float u_scale;

out vec4 frag_color;

// Mandelbrot set
//
// http://nuclear.mutantstargoat.com/articles/sdr_fract/
// https://en.wikipedia.org/wiki/Mandelbrot_set
//
// The Mandelbrot set is the set of complex numbers c
// for which the function f(z) = z^2 + c does not diverge when iterated from z = 0
// i.e., for which the sequence f(0), f(f(0)), etc., remains bounded in absolute value.
//
// Mandelbrot set images may be created by sampling the complex numbers and testing,
// for each sample point c, whether the sequence f(0), f(f(0)),... goes to infinity
// (in practice – whether it leaves some predetermined bounded neighborhood of 0
// after a predetermined number of iterations).
// Treating the real and imaginary parts of c as image coordinates on the complex plane,
// pixels may then be coloured according to how soon the sequence |f(0)|, |f(f(0))|,...
// crosses an arbitrarily chosen threshold, with a special color (usually black)
// used for the values of c for which the sequence has not crossed the threshold
// after the predetermined number of iterations (this is necessary to clearly distinguish
// the Mandelbrot set image from the image of its complement).

subroutine(fractalType)
vec3 mandelbrot(vec2 tex_coord) {
    vec3 color_red = vec3(0.9, 0.1, 0.1);
    vec3 color_yellow = vec3(1.0, 1.0, 0.0);
    vec3 color = vec3(0.0, 0.0, 0.0); // default black

    float x = 0.0;
    float y = 0.0;

    for (int iteration = 0; iteration < NUM_STEPS; iteration += 1) {
        float xtemp = x*x - y*y + tex_coord.x;
        y = 2.0*x*y + tex_coord.y;
        x = xtemp;

        if ( (x*x + y*y) >= 8.0) {
            float pct = float(iteration) / float(NUM_STEPS);
            // some custom (fixed) coloring
            if (pct < 0.15) {
                color = mix(color_red, color_yellow, smoothstep(0.0, 0.15, pct));
            } else {
                color = mix(color_yellow, color_red, smoothstep(0.15, 1.0, pct));
            }
            break;
        }
    }
    return color;
}

// If c in the above formula is held constant and the initial value of z is variable instead,
// one obtains the corresponding Julia set for each point c
// in the parameter space of the simple function.

subroutine(fractalType)
vec3 julia(vec2 tex_coord) {
    vec3 color_red = vec3(0.9, 0.1, 0.1);
    vec3 color_yellow = vec3(1.0, 1.0, 0.0);
    vec3 color = vec3(0.0, 0.0, 0.0); // default black

    float cr = u_julia_c.x;
    float ci = u_julia_c.y;

    float x = tex_coord.x;
    float y = tex_coord.y;

    for (int iteration = 0; iteration < NUM_STEPS; iteration += 1) {
        float xtemp = x*x - y*y + cr;
        y = 2.0*x*y + ci;
        x = xtemp;

        if ( (x*x + y*y) >= 8.0) {
            float pct = float(iteration) / float(NUM_STEPS);
            // some custom (fixed) coloring
            if (pct < 0.15) {
                color = mix(color_red, color_yellow, smoothstep(0.0, 0.15, pct));
            } else {
                color = mix(color_yellow, color_red, smoothstep(0.15, 1.0, pct));
            }
            break;
        }
    }
    return color;
}

void main() {
    // Step 1
    // Screen coordinates mapped to [-1,1] range, both in x and y direction
    // For example if canvas size is 640 x 480:
    // 480 -------------------              1 -------------------
    //     |                 |                |                 |
    //     |                 |    ==>         |                 |
    //     |                 |                |                 |
    //     |                 |                |                 |
    //   0 -------------------             -1 -------------------
    //     0                640              -1                 1
    vec2 tex_coord = (gl_FragCoord.xy / u_canvas_size.xy) * 2.0 - vec2(1.0, 1.0);

    // Step 2
    // Correct aspect ratio so we don't get distorted image
    // (if canvas size is square, than this is not needed)

    // If width is greater than height,
    // for example canvas width is 200, and height is 100,
    // than after the step above, we have situation on the left,
    // and we want it to be like the one on the right:
    //   1 -------------------            1 -------------------
    //     |                 |              |                 |
    //     |                 |    ==>       |                 |
    //     |                 |              |                 |
    //  -1 -------------------           -1 -------------------
    //    -1                 1             -2                 2
    //
    // and
    //
    // If height is greater than (or equal) to width,
    // for example canvas width is 100, and height is 200,
    // than after the step above, we have situation on the left,
    // and we want it to be like the one on the right:
    //   1 -------------            2 -------------
    //     |           |              |           |
    //     |           |    ==>       |           |
    //     |           |              |           |
    //     |           |              |           |
    //     |           |              |           |
    //     |           |              |           |
    //  -1 -------------           -2 -------------
    //    -1           1             -1           1
    //
    if (u_canvas_size.x > u_canvas_size.y) {
        float aspect = u_canvas_size.x / u_canvas_size.y;
        tex_coord.x *= aspect;
    } else {
        float aspect = u_canvas_size.y / u_canvas_size.x;
        tex_coord.y *= aspect;
    }

    // Step 3
    // Apply scale and offset
    // For example if scale = 2 and offset (-0.5,0)
    //   1 ---------------         //   2 ---------------
    //     |             |                |             |
    //     |             |    ==>         |             |
    //     |             |                |             |
    //     |             |                |             |
    //  -1 ---------------             -2 ---------------
    //    -1             1              -2.5           1.5
    tex_coord = tex_coord * u_scale + u_offset;

    // Calculate mandelbrot fractal color for given coordinate
    frag_color = vec4(fractal(tex_coord), 1.0);
}
