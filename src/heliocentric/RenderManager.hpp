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

#include "Renderer/MeshRenderer.hpp"
#include "Renderer/ShaderProgram.hpp"

class Game3D;

class RenderManager {
private:
	Game3D& game;
	std::vector<MeshRenderer*> renderers;
	std::vector<ShaderProgram*> programs;
	float gamma = 1;
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
	float getGamma() const {
		return gamma;
	}
	void setGamma(float gamma);
private:
	void forall (void (RenderManager::*f)(ShaderProgram&));
	void applyGamma(ShaderProgram& program);
	void uploadCameraToClipMatrix(ShaderProgram& program);
};

#endif	/* RENDERMANAGER_HPP */

