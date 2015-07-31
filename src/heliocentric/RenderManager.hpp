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
	/**
	 * Creates an instance of `RenderManager`.
	 * 
     * @param game the Game3D instance for this game
     * @param createDefaultRenderer if true, a `DefaultRenderer` is created with
	 * the default shaders provided by Heliocentric
     */
	RenderManager(Game3D& game, bool createDefaultRenderer = true);
	RenderManager(const RenderManager&) = delete;
	virtual ~RenderManager();
	/**
	 * Create the default renderer, as done by default by the constructor. 
     * @return a pointer to the new renderer
     */
	MeshRenderer* createDefaultRenderer();
	/**
	 * Creates a renderer of the type `DefaultRenderer` with a shader program 
	 * created from the given shader sources.
	 * 
     * @param vertexShader the source file of the vertex shader
     * @param geometryShader the source file of the geometry shader
     * @param fragmentShader the source file of the fragment shader
     * @param attributes a list of vertex attributes
     * @return a pointer to the new renderer
     */
	MeshRenderer* createRenderer(std::string vertexShader, std::string geometryShader,
			std::string fragmentShader, std::vector<std::string>* attributes = nullptr);
	/**
	 * Creates a renderer of the type `DefaultRenderer` with a shader program 
	 * created from the given shader sources.
	 * 
     * @param vertexShader the source file of the vertex shader
     * @param fragmentShader the source file of the fragment shader
     * @param attributes a list of vertex attributes
     * @return a pointer to the new renderer
     */
	MeshRenderer* createRenderer(std::string vertexShader, std::string fragmentShader,
			std::vector<std::string>* attributes = nullptr);
	/**
	 * Render the scene graph. 
	 * Additionally this method uploads changed lighting properties.
	 * 
     * @param base the base matrix
     */
	void render(glm::mat4 base);
	/**
	 * Returns the current value for the gamma correction.
	 * 
     * @return the gamma correction value
     */
	float getGamma() const {
		return gamma;
	}
	/**
	 * Set the value for gamma correction. Note that this expects the value to 
	 * correct for, as is done in any video game, not the gamma correction value.
	 * 
     * @param gamma the value for gamma correction
     */
	void setGamma(float gamma);
	/**
	 * Set parameters for the lighting - WILL MOST LIKELY CHANGE!
	 * 
     * @param sunLightColor
     * @param ambientIntensity
     * @param halfIntensityDistance
     */
	void setLightingProperties(glm::vec3 sunLightColor, float ambientIntensity, float halfIntensityDistance);
	/**
	 * Set the source location for the main lighting - WILL LIKELY CHANGE!
	 * 
     * @param sunPosition the location of the point source
     */
	void setSunPosition(glm::vec3 sunPosition);
	/**
	 * Add the game object to the scene graph to be rendered using the given 
	 * mesh and the default renderer. The default renderer is the first renderer
	 * created with this instance of `RenderManager`.
	 * 
     * @param obj the object to be rendered
     * @param mesh the mesh representing the object
     * @return the newly created scene graph node
     */
	Spatial* addToSceneGraph(GameObject& obj, Mesh& mesh);
	/**
	 * Add the game object to the scene graph to be rendered using the given 
	 * mesh and renderer.
	 * 
     * @param obj the object to be rendered
     * @param mesh the mesh representing the object
     * @param the renderer that is to be used to render the mesh
     * @return the newly created scene graph node
     */
	Spatial* addToSceneGraph(GameObject& obj, Mesh& mesh, MeshRenderer& renderer);
private:
	void initializeProgram(ShaderProgram& program);
	void forall (void (RenderManager::*f)(ShaderProgram&));
	void applyGamma(ShaderProgram& program);
	void uploadCameraToClipMatrix(ShaderProgram& program);
	void applyLightingProperties(ShaderProgram& program);
	void uploadSunPosition(ShaderProgram& program);
};

#endif	/* RENDERMANAGER_HPP */

