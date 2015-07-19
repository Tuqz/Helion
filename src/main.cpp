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

#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "heliocentric/Game3D.hpp"
#include "heliocentric/InputListener.hpp"
#include "heliocentric/GameInterface.hpp"
#include "heliocentric/ShaderProgram.hpp"
#include "heliocentric/loaders.hpp"
#include "heliocentric/Mesh.hpp"
#include "heliocentric/DefaultRenderer.hpp"
#include "heliocentric/SceneGraph/SceneGraph.hpp"
#include "heliocentric/SceneGraph/AbstractMeshNode.hpp"

using namespace std;

class Input : public InputListener {
private:
	Game3D& game;
	float movementSpeed = 1;
	float turnSpeed = 0.25;
public:

	Input(Game3D& game) : game(game) {
	};

	virtual void keyPressed(int key, int scancode, int mods) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				game.exit();
				break;
			case GLFW_KEY_W:
				game.getCamera().moveRelative(0, 0, -movementSpeed);
				break;
			case GLFW_KEY_S:
				game.getCamera().moveRelative(0, 0, movementSpeed);
				break;
			case GLFW_KEY_A:
				game.getCamera().moveRelative(-movementSpeed, 0, 0);
				break;
			case GLFW_KEY_D:
				game.getCamera().moveRelative(movementSpeed, 0, 0);
				break;
			case GLFW_KEY_SPACE:
				game.getCamera().moveRelative(0, movementSpeed, 0);
				break;
			case GLFW_KEY_X:
				game.getCamera().moveRelative(0, -movementSpeed, 0);
				break;
			case GLFW_KEY_KP_8:
				game.getCamera().tilt(turnSpeed);
				break;
			case GLFW_KEY_KP_5:
				game.getCamera().tilt(-turnSpeed);
				break;
			case GLFW_KEY_KP_4:
				game.getCamera().pan(-turnSpeed);
				break;
			case GLFW_KEY_KP_6:
				game.getCamera().pan(turnSpeed);
				break;
			case GLFW_KEY_KP_7:
				game.getCamera().roll(-turnSpeed);
				break;
			case GLFW_KEY_KP_9:
				game.getCamera().roll(turnSpeed);
				break;
			case GLFW_KEY_KP_0:
				game.getCamera().setPosition(vec3(0, 0, 2));
				game.getCamera().resetOrientation();
				break;
		}
	}

	virtual void keyReleased(int key, int scancode, int mods) {
	}

	virtual void keyRepeat(int key, int scancode, int mods) {
	}
};

class Helion : public GameInterface {
private:
	Game3D* game = nullptr;
	ShaderProgram* program = nullptr;
	Mesh* cube = nullptr;
	Node* ro = nullptr;
	DefaultRenderer renderer;
public:

	void setGame(Game3D* game) {
		this->game = game;
	}

	void init() {
		vector<string> attributes;
		attributes.push_back("position");
		program = new ShaderProgram("data/shaders/solid.vert", 
				"data/shaders/solid.frag", &attributes);

		// Load meshes;
		cube = loaders::loadOBJ("data/meshes/cube.obj");
//		cube->print();
		
		// Add Node to SceneGraph
		ro = new AbstractMeshNode(renderer, *cube);
		game->getScenegraph().addChild(ro);
		
		// Set camera-to-clip matrix
		int w, h;
		game->getWindow().getWindowSize(w, h);
		game->getCamera().updateAspect(w, h);
		glUseProgram(program->getProgram());
		glUniformMatrix4fv(program->getUniformLocation("cameraToClipMatrix"),
				1, GL_FALSE, value_ptr(game->getCamera().getCameraToClipMatrix()));
		glUseProgram(0);
		
		// Set initial camera location
		game->getCamera().setPosition(vec3(0, 0, 2));

		// Set clear color
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void renderHUD(glm::mat4 base) {
		game->getWindow().setTitle("Helion   -   "	+ to_string(game->getFPS()) + "fps");
	}

	void renderWorld(glm::mat4 base) {
		glUseProgram(program->getProgram());
		glUniformMatrix4fv(program->getUniformLocation("modelToCameraMatrix"),
				1, GL_FALSE, value_ptr(base));

		game->getScenegraph().render(base);

		glUseProgram(0);
	}

	bool shouldstop() {
		return false;
	}

	void shutdown() {
		delete program;
		delete cube;
		delete ro;
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

