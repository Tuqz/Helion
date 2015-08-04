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
private:
	const ShaderProgram& program;
public:
	DefaultRenderer(const ShaderProgram& program);
	DefaultRenderer(const DefaultRenderer& orig);
	virtual ~DefaultRenderer();
	virtual void render(Mesh& mesh, GLuint vao, glm::mat4 modelToCamera);
	virtual void setVertexAttribs();
	const ShaderProgram& getProgram() const {
		return program;
	}
};

#endif	/* DEFAULTRENDERER_HPP */

