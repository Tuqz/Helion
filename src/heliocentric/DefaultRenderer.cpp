/* 
 * File:   DefaultRenderer.cpp
 * Author: Ale Strooisma
 * 
 * Created on July 18, 2015, 3:27 PM
 */

#include <glm/mat4x4.hpp>

#include "DefaultRenderer.hpp"
#include "Mesh.hpp"

DefaultRenderer::DefaultRenderer() {
}

DefaultRenderer::DefaultRenderer(const DefaultRenderer& orig) {
}

DefaultRenderer::~DefaultRenderer() {
}

void DefaultRenderer::render(Mesh* mesh, GLuint vao, glm::mat4 modelToCamera) {
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void DefaultRenderer::setVertexAttribs() {
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}
