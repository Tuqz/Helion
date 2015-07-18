/* 
 * File:   Mesh.hpp
 * Author: Ale Strooisma
 *
 * Created on June 13, 2015, 2:18 PM
 */

#ifndef MESH_HPP
#define	MESH_HPP

#include <vector>
#include <GL/glew.h>

class Mesh {
private:
	std::vector<float> vertices;
	std::vector<unsigned short> indices;
	GLuint vbo, ibo;
public:
	Mesh(std::vector<float>& vertices, std::vector<unsigned short>& indices);
	Mesh(const Mesh& orig);
	virtual ~Mesh();

	const std::vector<float>& getVertices() const {
		return vertices;
	}
	
	const std::vector<unsigned short>& getIndices() const {
		return indices;
	}
	
	GLuint getIBO() const {
		return ibo;
	}

	GLuint getVBO() const {
		return vbo;
	}

	void print();
};

#endif	/* MESH_HPP */

