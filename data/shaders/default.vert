#version 130

in vec4 position;
in vec3 normal;

uniform mat4 cameraToClipMatrix;
uniform mat4 modelToCameraMatrix;

out vec3 vertexNormal;

void main() {
	vertexNormal = normal;

	vec4 cameraSpacePosition4 = modelToCameraMatrix * position;
	gl_Position = cameraToClipMatrix * cameraSpacePosition4;
}
