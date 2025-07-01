#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 pixelColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vec3 col;
    if(aPos.x < 0){
        col.x = aPos.x * -1;
    } else {
        col.x = aPos.x;
    }

    if(aPos.y < 0){
        col.y = aPos.y * -1;
    } else {
        col.y = aPos.y;
    }

    if(aPos.z < 0){
        col.z = aPos.z * -1;
    } else {
        col.z = aPos.z;
    }

    pixelColor = vec4(col, 1.0);
};