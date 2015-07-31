/* 
 * File:   RenderManager.hpp
 * Author: Ale Strooisma
 *
 * Created on July 29, 2015, 11:30 AM
 */

#ifndef RENDERMANAGER_HPP
#define	RENDERMANAGER_HPP

#include <vector>
#include <string>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Renderer/MeshRenderer.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "GameObject.hpp"
#include "SceneGraph/Spatial.hpp"

class Game3D;

class RenderManager {
private:
	Game3D& game;
	std::vector<MeshRenderer*> renderers;
	std::vector<ShaderProgram*> programs;
	std::vector<Spatial*> nodes;
	float gamma = 1;
	glm::vec3 sunLightColor = glm::vec3(1,1,1);
	float ambientIntensity = 0.05f;
	float halfIntensityDistance = 1;
	glm::vec3 sunPosition;
	glm::vec4 sunCameraPosition;
public:
	RenderManager(Game3D& game);
	RenderManager(const RenderManager&) = delete;
	virtual ~RenderManager();
	MeshRenderer* createDefaultRenderer();
	MeshRenderer* createRenderer(std::string vertexShader, std::string geometryShader,
			std::string fragmentShader, std::vector<std::string>* attributes = nullptr);
	MeshRenderer* createRenderer(std::string vertexShader, std::string fragmentShader,
			std::vector<std::string>* attributes = nullptr);
	void initializeProgram(ShaderProgram& program);
	void render(glm::mat4 base);
	float getGamma() const {
		return gamma;
	}
	void setGamma(float gamma);
	void setLightingProperties(glm::vec3 sunLightColor, float ambientIntensity, float halfIntensityDistance);
	void setSunPosition(glm::vec3 sunPosition);
	Spatial* addToSceneGraph(GameObject& obj, Mesh& mesh);
	Spatial* addToSceneGraph(GameObject& obj, Mesh& mesh, MeshRenderer& renderer);
private:
	void forall (void (RenderManager::*f)(ShaderProgram&));
	void applyGamma(ShaderProgram& program);
	void uploadCameraToClipMatrix(ShaderProgram& program);
	void applyLightingProperties(ShaderProgram& program);
	void uploadSunPosition(ShaderProgram& program);
};

#endif	/* RENDERMANAGER_HPP */

