/* 
 * File:   MeshObject.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 15, 2015, 5:40 PM
 */

#include <GL/glew.h>
#include <iostream>
#include "MeshObject.hpp"
#include "../Mesh.hpp"

using namespace std;

MeshObject::MeshObject(Mesh& mesh, GLuint& vao) : mesh(mesh), vao(vao) {
}

MeshObject::MeshObject(const MeshObject& orig) : MeshObject(orig.mesh, orig.vao) {
}

MeshObject::~MeshObject() {
}

void MeshObject::render() {
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, mesh.getIndices().size(), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}
