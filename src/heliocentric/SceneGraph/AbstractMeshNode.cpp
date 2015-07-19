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
#include "../MeshRenderer.hpp"
#include "../ShaderProgram.hpp"

using namespace std;

AbstractMeshNode::AbstractMeshNode(MeshRenderer& renderer, Mesh& mesh, ShaderProgram& program)
: renderer(renderer), mesh(mesh), program(program) {
	// Create the VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.getVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIBO());
	renderer.setVertexAttribs();
	glBindVertexArray(0);
}

AbstractMeshNode::AbstractMeshNode(const AbstractMeshNode& orig) 
: AbstractMeshNode(orig.renderer, orig.mesh, orig.program) {
}

AbstractMeshNode::~AbstractMeshNode() {
}

void AbstractMeshNode::render(glm::mat4 base) {
	renderer.render(mesh, program, vao, base);
}
