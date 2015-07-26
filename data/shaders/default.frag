#version 130

in vec3 vertexNormal;

smooth in vec4 fragColor;

out vec4 outputColor;

void main() {
    outputColor = vec4((vertexNormal+1)/2, 1.0f);
}
