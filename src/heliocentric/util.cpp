#include <GLFW/glfw3.h>

void getCurrentResolution(int* width, int* height) {
	const GLFWvidmode* return_struct = glfwGetVideoMode(glfwGetPrimaryMonitor());
	*height = return_struct->height;
	*width = return_struct->width;
}

bool glversion(int requiredMajor, int requiredMinor) {
	int actualMajor, actualMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &actualMajor);
	glGetIntegerv(GL_MINOR_VERSION, &actualMinor);
	if (requiredMajor < actualMajor) {
		return true;
	}
	if (requiredMajor > actualMajor) {
		return false;
	}
	return requiredMinor <= actualMinor;
}