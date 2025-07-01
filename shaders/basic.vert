#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 tpos;
layout (location = 2) in vec3 aNormal;

out vec2 texPos;
out vec4 bPos;
out vec3 Normal;
out vec3 pixelPos;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main() {
    mat4 finalModel = u_model;
    gl_Position = u_projection * u_view * finalModel * aPos;
    bPos = aPos;
    texPos = tpos;

    Normal = mat3(transpose(inverse(u_view * finalModel))) * aNormal; 
    pixelPos = vec3(finalModel * aPos);
}
