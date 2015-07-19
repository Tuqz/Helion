/* 
 * File:   DefaultRenderer.hpp
 * Author: Ale Strooisma
 *
 * Created on July 18, 2015, 3:27 PM
 */

#ifndef DEFAULTRENDERER_HPP
#define	DEFAULTRENDERER_HPP

#include <GL/glew.h>
#include "MeshRenderer.hpp"

class DefaultRenderer : public MeshRenderer {
public:
	DefaultRenderer();
	DefaultRenderer(const DefaultRenderer& orig);
	virtual ~DefaultRenderer();
	virtual void render(Mesh& mesh, ShaderProgram& program, GLuint vao, glm::mat4 modelToCamera);
	virtual void setVertexAttribs();
};

#endif	/* DEFAULTRENDERER_HPP */

