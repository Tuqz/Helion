#version 130

in vec4 position;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

void main() {
	vec4 cameraSpacePosition4 = modelToCameraMatrix * position;
	gl_Position = cameraToClipMatrix * cameraSpacePosition4;
}
