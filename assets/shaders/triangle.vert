#version 460 core

uniform mat4 view_proj;

vec2 vertices[3] = vec2[](
vec2(0.0, 0.5),
vec2(-0.5, -0.5),
vec2(0.5, -0.5)
);

void main() {
    gl_Position = view_proj * vec4(vertices[gl_VertexID], 0.0, 1.0);
}
