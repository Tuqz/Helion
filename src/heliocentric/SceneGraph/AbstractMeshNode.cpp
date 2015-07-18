/* 
 * File:   MeshObject.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 15, 2015, 5:40 PM
 */

#include "AbstractMeshNode.hpp"

#include <iostream>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "../Mesh.hpp"

using namespace std;

AbstractMeshNode::AbstractMeshNode(MeshRenderer& renderer, Mesh& mesh) : renderer(renderer), mesh(mesh) {

	// Create a VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIBO());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}

AbstractMeshNode::AbstractMeshNode(const AbstractMeshNode& orig) : AbstractMeshNode(orig.renderer, orig.mesh) {
}

AbstractMeshNode::~AbstractMeshNode() {
}

void AbstractMeshNode::render(glm::mat4 base) {
	renderer.render(&mesh, vao, base);
}
