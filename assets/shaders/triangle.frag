#version 460 core

layout(location = 0) in vec2 v_uv;

layout(location = 0) out vec4 frag_color;

layout(location = 0) uniform sampler2D u_texture;

void main() {
    frag_color = texture(u_texture, v_uv);
}
