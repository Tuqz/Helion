/* 
 * File:   MeshObject.hpp
 * Author: Ale Strooisma
 *
 * Created on June 15, 2015, 5:40 PM
 */

#ifndef SCENEGRAPH_ABSTRACTMESHNODE_HPP
#define	SCENEGRAPH_ABSTRACTMESHNODE_HPP

#include <GL/glew.h>

#include "Node.hpp"
#include "../MeshRenderer.hpp"


class Mesh;

class AbstractMeshNode : public Node {
private:
	GLuint vao;
	MeshRenderer& renderer;
	Mesh& mesh;
public:
	AbstractMeshNode(MeshRenderer& renderer, Mesh& mesh);
	AbstractMeshNode(const AbstractMeshNode& orig);
	virtual ~AbstractMeshNode();
	virtual void render(glm::mat4 base);
	
	GLuint getVAO() const {
		return vao;
	}
};

#endif	/* SCENEGRAPH_ABSTRACTMESHNODE_HPP */

