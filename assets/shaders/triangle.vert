#version 460 core

layout(location = 0) out vec2 v_uv;

uniform mat4 view_proj;

vec2 vertices[6] = vec2[](
vec2(-0.5, -0.5),
vec2(-0.5, 0.5),
vec2(0.5, 0.5),
vec2(0.5, 0.5),
vec2(0.5, -0.5),
vec2(-0.5, -0.5)
);

vec2 uv[6] = vec2[](
vec2(0.0, 0.0),
vec2(0.0, 1.0),
vec2(1.0, 1.0),
vec2(1.0, 1.0),
vec2(1.0, 0.0),
vec2(0.0, 0.0)
);

void main() {
    v_uv = uv[gl_VertexID];
    gl_Position = view_proj * vec4(vertices[gl_VertexID], 0.0, 1.0);
}
