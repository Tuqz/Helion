#include <vector>
#include <string>

#define GLM_FORCE_RADIANS

#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include "heliocentric/GameInterface.hpp"
#include "heliocentric/Game3D.hpp"
#include "heliocentric/GameObject.hpp"
#include "heliocentric/DefaultRenderer.hpp"
#include "heliocentric/Mesh.hpp"
#include "heliocentric/loaders.hpp"
#include "heliocentric/SceneGraph/Spatial.hpp"
#include "orbits/bodyloader.h"
#include "orbits/celestialbody.h"


class PlanetObject : public GameObject {
private:
	glm::quat orientation;
public:
	helion::CelestialBody body;
	Mesh *mesh;
	Spatial node;
	PlanetObject(helion::CelestialBody &b) {
		body = b;
		orientation = glm::quat();
		mesh = loaders::loadOBJ("data/meshes/cube.obj");
	}

	virtual glm::vec3 getPosition() {
		return body.position/1e24; //Scale position down to a much more handlable scale
	}

	virtual glm::quat getOrientation() {
		return orientation;
	}
};

class OrbitTest : public GameInterface {
private:
	DefaultRenderer renderer;
	ShaderProgram program;
	helion::Orbitable Sol;
	std::vector<PlanetObject> system;
	Game3D *game;
	double t = 0;
public:
	void init() {
		std::vector<std::string> attributes;
		attributes.push_back("position");
		program = ShaderProgram("data/shaders/solid.vert", "data/shaders/solid.frag", &attributes);
		
		Sol = helion::loadSun("data/physics/sol.dat");
		helion::SolarSystem solar_system = helion::loadSystem(Sol, "data/physics/system.dat");
		int i = 0;
		for(auto keyvalue : solar_system) {
			keyvalue.second.update(0); //Send them to the J2000 epoch
			PlanetObject obj(keyvalue.second);
			system.push_back(obj);
			Spatial node(renderer, *(system[i].mesh), program, &system[i]);
			system[i].node = node;
			game->getScenegraph().addChild(&system[i].node);
			++i;
		}
	}
	
	void update(double dt) {
		t += (dt * 1e6); //Speed up time 1,000,000x
		for(auto body : system) {
			body.body.update(t);
		}
	}

	void renderWorld(glm::mat4 base) {
		game->getScenegraph().render(base);
	}

	void renderHUD(glm::mat4 base) {
		game->getWindow().setTitle("Test");
	}

	bool shouldstop() {
		return false;
	}

	void setGame(Game3D *g) {
		game = g;
	}

	void shutdown() {
	}
};

int main() {
	OrbitTest test;
	Game3D game(test);
	game.run();
	return 0;
}
