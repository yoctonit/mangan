#version 430

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

out vec2 tex_coords;

uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * vec4(vertex.xy, 0.0, 1.0);
    tex_coords = vertex.zw;
}
