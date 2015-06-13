/* 
 * File:   Mesh.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 13, 2015, 2:18 PM
 */

#include <iostream>
#include "Mesh.hpp"

using namespace std;

Mesh::Mesh(vector<float>& vertices, vector<unsigned short>& indices)
: vertices(vertices), indices(indices) {
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

