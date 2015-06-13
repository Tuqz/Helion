/* 
 * File:   Mesh.hpp
 * Author: Ale Strooisma
 *
 * Created on June 13, 2015, 2:18 PM
 */

#ifndef MESH_HPP
#define	MESH_HPP

#include <vector>

class Mesh {
private:
	std::vector<float> vertices;
	std::vector<unsigned short> indices;
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
	
	void print();
};

#endif	/* MESH_HPP */

