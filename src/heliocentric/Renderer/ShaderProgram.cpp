/* 
 * File:   ShaderProgram.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 8, 2015, 5:04 PM
 */

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <errno.h>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.hpp"
#include "../exceptions.hpp"

using namespace std;

string getName(int shaderType) {
	if (shaderType == GL_VERTEX_SHADER) {
		return "vertex";
	}
	if (shaderType == GL_GEOMETRY_SHADER) {
		return "geometry";
	}
	if (shaderType == GL_FRAGMENT_SHADER) {
		return "fragment";
	}
	return "<unknown type>";
}

string loadShader(string filename) {
	// Open the file
	ifstream file(filename);
	if (!file.is_open()) {
		throw IOException("Cannot read file \"" + filename + "\": " + strerror(errno) + ".");
	}

	// Load file into buffer
	stringstream buffer;
	buffer << file.rdbuf();
	if (file.bad()) {
		throw IOException("Error while reading file \"" + filename + "\": " + strerror(errno) + ".");
	}

	// Return buffer contents
	return buffer.str();
}

int createShader(int shaderType, string filename) {
	// Create the actual shader
	int shader = glCreateShader(shaderType);
	string shaderSource = loadShader(filename);
	const char *c_str = shaderSource.c_str();
	glShaderSource(shader, 1, &c_str, NULL);
	glCompileShader(shader);

	// Error handling
	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		int logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		char log[logLength];
		glGetShaderInfoLog(shader, logLength, &logLength, log);
		string msg = string("Failure in compiling ")
				+ getName(shaderType) + " shader. " + "Error log:\n" + log;
		throw ShaderException(msg);
	}

	// Return the shader upon success
	return shader;
}

ShaderProgram::ShaderProgram(string vertexShader, string fragmentShader)
: ShaderProgram(vertexShader, "", fragmentShader) {
}

ShaderProgram::ShaderProgram(string vertexShader, string fragmentShader, vector<string>* attributes)
: ShaderProgram(vertexShader, "", fragmentShader, attributes) {
}

ShaderProgram::ShaderProgram(string vertexShader, string geometryShader, string fragmentShader)
: ShaderProgram(vertexShader, geometryShader, fragmentShader, nullptr) {
}

ShaderProgram::ShaderProgram(string vertexShader, string geometryShader,
		string fragmentShader, vector<string>* attributes) {
	// Create the shaders
	int vs = createShader(GL_VERTEX_SHADER, vertexShader);
	int gs = -1;
	if (geometryShader.compare("")) {
		createShader(GL_GEOMETRY_SHADER, geometryShader);
	}
	int fs = createShader(GL_FRAGMENT_SHADER, fragmentShader);

	// Create the program
	program = glCreateProgram();

	// Attach the shaders
	glAttachShader(program, vs);
	if (gs != -1) {
		glAttachShader(program, gs);
	}
	glAttachShader(program, fs);

	// Bind the shader attributes
	if (attributes != nullptr) {
		for (int i = 0; i < attributes->size(); i++) {
			glBindAttribLocation(program, i, attributes->at(i).c_str());
		}
	}

	// Link the Program
	glLinkProgram(program);

	// Error handling
	int status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		int logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		char log[logLength];
		glGetProgramInfoLog(program, logLength, &logLength, log);
		string msg = string("Failure in linking program. Error log:\n") + log;
		throw ShaderException(msg);
	}

	// Clean up
	glDetachShader(program, vs);
	if (gs != -1) {
		glDetachShader(program, gs);
	}
	glDetachShader(program, fs);

	glDeleteShader(vs);
	if (gs != -1) {
		glDeleteShader(gs);
	}
	glDeleteShader(fs);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(program);
}

GLuint ShaderProgram::getProgram() {
	return program;
}

GLint ShaderProgram::getUniformLocation(string name) {
	return glGetUniformLocation(program, name.c_str());
}

GLuint ShaderProgram::getUniformBlockIndex(string name) {
	return glGetUniformBlockIndex(program, name.c_str());
}