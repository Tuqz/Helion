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
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define PI 3.14159265359f

#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "heliocentric/Game3D.hpp"
#include "heliocentric/input/InputAdaptor.hpp"
#include "heliocentric/GameAdaptor.hpp"
#include "heliocentric/ObjLoader.hpp"
#include "heliocentric/renderer/Mesh.hpp"
#include "heliocentric/renderer/DefaultRenderer.hpp"
#include "heliocentric/renderer/ShaderProgram.hpp"
#include "heliocentric/GameObject.hpp"
#include "heliocentric/scenegraph/SceneGraph.hpp"
#include "heliocentric/scenegraph/Spatial.hpp"
#include "heliocentric/RenderManager.hpp"
#include "heliocentric/input/InputEventQueue.hpp"
#include "heliocentric/input/InputEvent.hpp"
#include "heliocentric/camera/CameraManager.hpp"
#include "heliocentric/camera/OrbitingCameraModel.hpp"

using namespace std;

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

	void setPosition(glm::vec3 position) {
		this->position = position;
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

class Helion : public GameAdaptor {
private:
	Game3D* game = nullptr;
	InputEventQueue* eventQueue;
	Mesh* cube = nullptr;
	Mesh* sphere = nullptr;
	Mesh* square = nullptr;
	TestObject* obj1 = nullptr, * obj2 = nullptr, * obj3 = nullptr;
	TestObject* sun = nullptr;
	RenderManager* manager = nullptr;
	CameraManager* cams = nullptr;
	OrbitingCameraModel ocm;
	double t = 0;
	
	// Texture stuff
	vector<GLubyte> textureData;
	int texturesize = 512;
	GLuint texture, samplerObject;
	ShaderProgram* textureShader = nullptr;
	MeshRenderer* textureRenderer = nullptr;
	TestObject* textureObject = nullptr;
	int textureUnit = 0;
public:

	Helion(InputEventQueue* eventQueue) : GameAdaptor(), eventQueue(eventQueue) {
	}

	void setGame(Game3D* game) {
		this->game = game;
	}

	void init() {
		// Set up managers
		manager = new RenderManager(*game);
		cams = new CameraManager(*game);
		game->addInputListener(cams);
		cams->addModel("orbit", &ocm);
		manager->setGamma(2.2f);

		// Add an extra shader because I want a white 'sun'
		vector<string> attributes;
		attributes.push_back("position");
		attributes.push_back("normal");
		DefaultRenderer* whiteRenderer = (DefaultRenderer*)
				manager->createRenderer("data/shaders/default.vert",
				"data/shaders/white.frag", &attributes);

		// Load meshes
		ObjLoader loader;
		cube = loader.load("data/meshes/cube.obj");
		sphere = loader.load("data/meshes/sphere.obj");
		square = loader.load("data/meshes/test.obj");

		// Create game objects
		obj1 = new TestObject(glm::vec3(1, 0, 0));
		obj2 = new TestObject(glm::vec3(-1, 0.5f, -2));
		obj2->rotate(PI / 8, 0, 1, 0);
		obj3 = new TestObject(glm::vec3(-0.5f, -1, -1));
		obj3->rotate(PI / 4, 1, 0, 0);
		sun = new TestObject(glm::vec3(-1, 0, 1));

		// Add game objects to SceneGraph
		manager->addToSceneGraph(*obj1, *cube);
		manager->addToSceneGraph(*obj2, *cube);
		manager->addToSceneGraph(*obj3, *cube);
		manager->addToSceneGraph(*sun, *sphere, *whiteRenderer)->setScale(0.2f);
		
		initTextureTest();

		// Set initial camera location (default is 0,0,0)
		game->getCamera().setPosition(vec3(0, 0, 2));

		// Set source position of sunlight (default is 0,0,0)
		manager->setSunPosition(sun->getPosition());

		// Set sun as camera focus
		cams->focusOn(sun);

		// Set clear color
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void initTextureTest() {
		// Texture shaders
		vector<string> attributes;
		attributes.push_back("position");
		attributes.push_back("normal");
//		textureShader = new ShaderProgram("data/shaders/texture.vert", 
//				"data/shaders/texture.frag", &attributes);
		DefaultRenderer* texRenderer = (DefaultRenderer*)
				manager->createRenderer("data/shaders/texture.vert",
				"data/shaders/texture.frag", &attributes);
		
		// Build texture
		for (float i = 0; i < texturesize; i++) {
			textureData.push_back(sin(PI * i / (texturesize - 1))*255.0f);
		}

		// Upload texture
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_1D, texture);
		glTexImage1D(GL_TEXTURE_1D, 0, GL_R8, texturesize, 0,
				GL_RED, GL_UNSIGNED_BYTE, &textureData[0]);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAX_LEVEL, 0);
		glBindTexture(GL_TEXTURE_1D, 0);
		
		// Link sampler to texture unit
		glUseProgram(texRenderer->getProgram().getProgram());
		glUniform1i(texRenderer->getProgram().getUniformLocation("redTexture"), textureUnit);
		
		// Link texture to texture unit
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_1D, texture);
		
		// Sampler object
		glGenSamplers(1, &samplerObject);
		glSamplerParameteri(samplerObject, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glSamplerParameteri(samplerObject, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glSamplerParameteri(samplerObject, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glBindSampler(textureUnit, samplerObject);
		
		// Demo object
		textureObject = new TestObject(glm::vec3(0.5, 0.5, 0.5));
		manager->addToSceneGraph(*textureObject, *square, *texRenderer);
	}
	
	virtual void update(double dt) {
		InputEvent* event;
		while (event = eventQueue->nextEvent()) {
			if (event->getType() == InputEventType::MOUSE_BUTTON_PRESSED) {
				cout << "Boop!" << endl;
			}
		}

		t += dt;
		sun->setPosition(vec3(-1 + sin(t), 0, 0.75));
		manager->setSunPosition(sun->getPosition());
		obj3->rotate(dt, 1, 0, 0);

		cams->update(dt);
	}

	void renderHUD(glm::mat4 base) {
		game->getWindow().setTitle("Helion   -   " + to_string(game->getFPS()) + "fps");
	}

	void renderWorld(glm::mat4 base) {
		manager->render(base);
	}

	void shutdown() {
		delete manager;
		delete cams;
		delete cube;
		delete sphere;
		delete square;
		delete obj1;
		delete obj2;
		delete obj3;
		delete sun;
		delete textureShader;
		delete textureRenderer;
	}

	CameraManager* getCameraManager() const {
		return cams;
	}

};

class Input : public InputAdaptor {
private:
	Game3D& game;
	Helion& helion;
	float movementSpeed = 0.1;
	float turnSpeed = 0.025;
public:

	Input(Game3D& game, Helion& helion) : game(game), helion(helion) {
	};

	virtual bool keyPressed(int key, int scancode, int mods, bool repeat) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				game.exit();
				return true;
			case GLFW_KEY_C:
			case GLFW_KEY_V:
				helion.getCameraManager()->nextModel();
				return true;
			case GLFW_KEY_KP_8:
				game.getCamera().tilt(turnSpeed);
				return true;
			case GLFW_KEY_KP_5:
				game.getCamera().tilt(-turnSpeed);
				return true;
			case GLFW_KEY_KP_4:
				game.getCamera().pan(-turnSpeed);
				return true;
			case GLFW_KEY_KP_6:
				game.getCamera().pan(turnSpeed);
				return true;
			case GLFW_KEY_KP_7:
				game.getCamera().roll(-turnSpeed);
				return true;
			case GLFW_KEY_KP_9:
				game.getCamera().roll(turnSpeed);
				return true;
			case GLFW_KEY_KP_0:
				game.getCamera().setPosition(vec3(0, 0, 2));
				game.getCamera().resetOrientation();
				return true;
		}
		return false;
	}
};

/*
 * Boots Helion
 */
int main(int argc, char** argv) {
	InputEventQueue eventQueue;

	Helion helion(&eventQueue);
	Game3D game(helion);

	Input listener(game, helion);
	game.addInputListener(&eventQueue);
	game.addInputListener(&listener);

	game.run();

	return 0;
}

