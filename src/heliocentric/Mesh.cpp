/* 
 * File:   Mesh.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 13, 2015, 2:18 PM
 */
#include "Mesh.hpp"

#include <iostream>

#include <GL/glew.h>

using namespace std;

Mesh::Mesh(vector<float>& vertices, vector<unsigned short>& indices)
: vertices(vertices), indices(indices) {

	// Create vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
			vertices.size() * sizeof (float),
			vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create index buffer
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof (unsigned short),
			indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
}

void Mesh::print() {
	cout << "Number of vertices: " << vertices.size() << endl << "Vertices: ";
	for (int i = 0; i < vertices.size(); i++) {
		cout << vertices[i] << " ";
	}
	cout << endl;
	cout << "Number of indices: " << indices.size() << endl << "Indices: ";
	for (int i = 0; i < indices.size(); i++) {
		cout << indices[i] << " ";
	}
	cout << endl;
}

