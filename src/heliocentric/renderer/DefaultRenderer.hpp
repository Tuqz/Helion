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
class Texture;

class DefaultRenderer : public MeshRenderer {
private:
	const ShaderProgram& program;
public:
	DefaultRenderer(const ShaderProgram& program);
	virtual ~DefaultRenderer() = default;
	virtual void render(glm::mat4 modelToCamera, Mesh& mesh, GLuint vao, const Texture* texture);
	virtual void setVertexAttribs();
	const ShaderProgram& getProgram() const {
		return program;
	}
};

#endif	/* DEFAULTRENDERER_HPP */

