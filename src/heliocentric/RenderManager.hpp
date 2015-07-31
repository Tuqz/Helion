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


class RenderManager {
private:
	std::vector<MeshRenderer*> renderers;
	std::vector<ShaderProgram*> programs;
public:
	RenderManager();
	RenderManager(const RenderManager&) = delete;
	virtual ~RenderManager();
	MeshRenderer* createDefaultRenderer();
	MeshRenderer* createRenderer(std::string vertexShader, std::string geometryShader,
			std::string fragmentShader, std::vector<std::string>* attributes = nullptr);
	MeshRenderer* createRenderer(std::string vertexShader, std::string fragmentShader,
			std::vector<std::string>* attributes = nullptr);
	void initializeProgram(ShaderProgram& program);
};

#endif	/* RENDERMANAGER_HPP */

