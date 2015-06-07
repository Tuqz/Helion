#include <GLFW/glfw3.h>

void getCurrentResolution(int* width, int* height) {
	const GLFWvidmode* return_struct = glfwGetVideoMode(glfwGetPrimaryMonitor());
	*height = return_struct->height;
	*width = return_struct->width;
}