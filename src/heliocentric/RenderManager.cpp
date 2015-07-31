/* 
 * File:   RenderManager.cpp
 * Author: Ale Strooisma
 * 
 * Created on July 29, 2015, 11:30 AM
 */

#include "RenderManager.hpp"
#include "Renderer/DefaultRenderer.hpp"
#include "exceptions.hpp"
#include "Game3D.hpp"

#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

RenderManager::RenderManager(Game3D& game) : game(game) {
}

RenderManager::~RenderManager() {
	for (vector<MeshRenderer*>::iterator it = renderers.begin(); it != renderers.end(); ++it) {
		delete *it;
	}
	for (vector<ShaderProgram*>::iterator it = programs.begin(); it != programs.end(); ++it) {
		delete *it;
	}
}

MeshRenderer* RenderManager::createDefaultRenderer() {
	vector<string> attributes;
	attributes.push_back("position");
	attributes.push_back("normal");
	createRenderer("data/shaders/default.vert",
			"data/shaders/default.frag", &attributes);
}

MeshRenderer* RenderManager::createRenderer(string vertexShader,
		string fragmentShader, vector<string>* attributes) {
	return createRenderer(vertexShader, "", fragmentShader, attributes);
}

MeshRenderer* RenderManager::createRenderer(string vertexShader,
		string geometryShader, string fragmentShader, vector<string>* attributes) {
	programs.push_back(new ShaderProgram(vertexShader, geometryShader, fragmentShader, attributes));
	initializeProgram(*(programs.back()));
	renderers.push_back(new DefaultRenderer(*(programs.back())));
	return renderers.back();
}

void RenderManager::initializeProgram(ShaderProgram& program) {
	glUseProgram(program.getProgram());
	uploadCameraToClipMatrix(program);
	applyGamma(program);
	glUseProgram(0);
}

void RenderManager::forall(void (RenderManager::*f)(ShaderProgram&)) {
	for (vector<ShaderProgram*>::iterator it = programs.begin(); it != programs.end(); ++it) {
		glUseProgram((*it)->getProgram());
		(this->*f)(**it);
		glUseProgram(0);
	}
}

void RenderManager::setGamma(float gamma) {
	this->gamma = gamma;
	forall(&RenderManager::applyGamma);
}

void RenderManager::applyGamma(ShaderProgram& program) {
	glUniform1f(program.getUniformLocation("invgamma"), 1.0f/gamma);
}

void RenderManager::uploadCameraToClipMatrix(ShaderProgram& program) {
	glUniformMatrix4fv(program.getUniformLocation("cameraToClipMatrix"),
			1, GL_FALSE, value_ptr(game.getCamera().getCameraToClipMatrix()));
}