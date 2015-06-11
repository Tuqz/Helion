#version 130

in vec4 position;
in vec4 color;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

smooth out vec4 fragColor;

void main() {
    fragColor = color;
	vec4 cameraSpacePosition4 = modelToCameraMatrix * position;
	gl_Position = cameraToClipMatrix * cameraSpacePosition4;
}
