#version 330 core

out vec4 FragColor;
// in  vec4 pixelColor;
in  vec2 texturePosition;

uniform sampler2D texture;

void main() {
    FragColor = texture(texture, texturePosition); // pixelColor;
}
