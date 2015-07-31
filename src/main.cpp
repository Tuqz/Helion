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

#define PI 3.14159265359f

#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "heliocentric/Game3D.hpp"
#include "heliocentric/InputListener.hpp"
#include "heliocentric/GameInterface.hpp"
#include "heliocentric/ObjLoader.hpp"
#include "heliocentric/Renderer/Mesh.hpp"
#include "heliocentric/Renderer/DefaultRenderer.hpp"
#include "heliocentric/Renderer/ShaderProgram.hpp"
#include "heliocentric/GameObject.hpp"
#include "heliocentric/SceneGraph/SceneGraph.hpp"
#include "heliocentric/SceneGraph/Spatial.hpp"
#include "heliocentric/RenderManager.hpp"

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

class TestObject : public GameObject {
private:
	glm::vec3 position;
	glm::quat orientation;
public:

	TestObject(glm::quat orientation, glm::vec3 position)
	: orientation(orientation), position(position) {
	}

	TestObject(glm::vec3 position) : TestObject(glm::quat(), position) {
	}

	virtual glm::vec3 getPosition() {
		return position;
	}

	virtual glm::quat getOrientation() {
		return orientation;
	}

	void rotate(float angle, float x, float y, float z) {
		float f = sinf(angle / 2.0f);
		glm::quat q = quat(cosf(angle / 2.0f), x*f, y*f, z * f);
		orientation = normalize(q * orientation);
	}
};

class Helion : public GameInterface {
private:
	Game3D* game = nullptr;
	Mesh* cube = nullptr;
	Mesh* sphere = nullptr;
	Spatial* node1 = nullptr, * node2 = nullptr, * node3 = nullptr;
	TestObject* obj1 = nullptr, * obj2 = nullptr, * obj3 = nullptr;
	TestObject* sun = nullptr;
	Spatial* sunnode = nullptr;
	DefaultRenderer* defaultRenderer = nullptr;
	DefaultRenderer* whiteRenderer = nullptr;
	RenderManager* manager = nullptr;
public:

	void setGame(Game3D* game) {
		this->game = game;
	}

	void init() {
		manager = new RenderManager(*game);
		
		// Prepare shaders and renderers
		vector<string> attributes;
		attributes.push_back("position");
		attributes.push_back("normal");
		defaultRenderer = (DefaultRenderer*) manager->createRenderer("data/shaders/default.vert",
				"data/shaders/default.frag", &attributes);
//				"data/shaders/normals.frag", &attributes);
		whiteRenderer = (DefaultRenderer*) manager->createRenderer("data/shaders/default.vert",
				"data/shaders/white.frag", &attributes);
		const ShaderProgram& program = defaultRenderer->getProgram();

		// Load meshes
		ObjLoader loader;
		cube = loader.load("data/meshes/cube.obj");
		sphere = loader.load("data/meshes/sphere.obj");

		// Add meshes to SceneGraph
		obj1 = new TestObject(glm::vec3(1, 0, 0));
		node1 = new Spatial(*defaultRenderer, *cube, *obj1);
		game->getScenegraph().addChild(node1);

		obj2 = new TestObject(glm::vec3(-1, 0.5f, -2));
		obj2->rotate(PI / 8, 0, 1, 0);
		node2 = new Spatial(*defaultRenderer, *cube, *obj2);
		game->getScenegraph().addChild(node2);

		obj3 = new TestObject(glm::vec3(-0.5f, -1, -1));
		obj3->rotate(PI / 4, 1, 0, 0);
		node3 = new Spatial(*defaultRenderer, *cube, *obj3);
		game->getScenegraph().addChild(node3);

		sun = new TestObject(glm::vec3(-1, 0, 1));
		sunnode = new Spatial(*whiteRenderer, *sphere, *sun);
		sunnode->setScale(0.2f);
		game->getScenegraph().addChild(sunnode);
		manager->setSunPosition(sun->getPosition());
		
		// Set initial camera location
		game->getCamera().setPosition(vec3(0, 0, 2));

		// Set clear color
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void renderHUD(glm::mat4 base) {
		game->getWindow().setTitle("Helion   -   " + to_string(game->getFPS()) + "fps");
	}

	void renderWorld(glm::mat4 base) {
		manager->render(base);
	}

	bool shouldStop() {
		return false;
	}
	
	void windowResized(int width, int height) {
	}
	
	bool windowClosed() {
		return false;
	}
	

	void shutdown() {
		delete manager;
		delete cube;
		delete sphere;
		delete node1;
		delete node2;
		delete node3;
		delete obj1;
		delete obj2;
		delete obj3;
		delete sun;
		delete sunnode;
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

