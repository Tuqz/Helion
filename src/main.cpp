/* 
 * File:   main.cpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 12:38 PM
 */

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

#include "heliocentric/Game3D.hpp"
#include "heliocentric/InputListener.hpp"
#include "heliocentric/GameInterface.hpp"
#include "heliocentric/ShaderProgram.hpp"

using namespace std;

const float vertices[] = {
	0.75f, 0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
};

class Input : public InputListener {
private:
	Game& game;
public:

	Input(Game& game) : game(game) {
	};

	virtual void keyPressed(int key, int scancode, int mods) {
		if (key == GLFW_KEY_ESCAPE) {
			game.exit();
		}
	}

	virtual void keyReleased(int key, int scancode, int mods) {
	}

	virtual void keyRepeat(int key, int scancode, int mods) {
	}
};

class Helion : public GameInterface {
private:
	GLuint vao, vbo;
	ShaderProgram* program;
public:
	void init() {
		program = new ShaderProgram("data/shaders/wip.vert", "data/shaders/wip.frag");

		// Initialize vertex buffer
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void renderHUD(glm::mat4 base) {
	}

	void renderWorld(glm::mat4 base) {	
		glUseProgram(program->getProgram());

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glUseProgram(0);
	}

	bool shouldstop() {
		return false;
	}

	void shutdown() {
	}

	void update(double dt) {
	}
};

/*
 * Boots Helion
 */
int main(int argc, char** argv) {
	Helion helion;
	Game3D game(helion);
	Input listener(game);
	game.setInputListener(&listener);
	game.run();
	return 0;
}

