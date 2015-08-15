/* 
 * File:   MeshRenderer.hpp
 * Author: Ale Strooisma
 *
 * Created on June 18, 2015, 9:14 PM
 */

#ifndef MESHRENDERER_HPP
#define	MESHRENDERER_HPP

#include <GL/glew.h>
#include <glm/fwd.hpp>
class Mesh;
class ShaderProgram;
class Texture;

class MeshRenderer {
public:
	virtual ~MeshRenderer() {};
	virtual void render(glm::mat4 modelToCamera, Mesh& mesh, GLuint vao, const Texture* texture = nullptr) = 0;
	virtual void setVertexAttribs() = 0;
};

#endif	/* MESHRENDERER_HPP */

