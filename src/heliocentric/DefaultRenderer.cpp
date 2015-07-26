/* 
 * File:   DefaultRenderer.cpp
 * Author: Ale Strooisma
 * 
 * Created on July 18, 2015, 3:27 PM
 */

#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DefaultRenderer.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"

DefaultRenderer::DefaultRenderer() {
}

DefaultRenderer::DefaultRenderer(const DefaultRenderer& orig) {
}

DefaultRenderer::~DefaultRenderer() {
}

void DefaultRenderer::render(Mesh& mesh, ShaderProgram& program, GLuint vao, glm::mat4 modelToCamera) {
	glUseProgram(program.getProgram());
	glUniformMatrix4fv(program.getUniformLocation("modelToCameraMatrix"),
			1, GL_FALSE, glm::value_ptr(modelToCamera));

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, mesh.getIndices().size(), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
	
	glUseProgram(0);
}

void DefaultRenderer::setVertexAttribs() {
	// Vertex coordinates
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
	// Vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*) (4*sizeof(float)));
}
