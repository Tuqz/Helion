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
class Mesh;
class MeshRenderer;
class ShaderProgram;


class Mesh;

class AbstractMeshNode : public Node {
private:
	GLuint vao;
	MeshRenderer& renderer;
	Mesh& mesh;
	ShaderProgram& program;
public:
	AbstractMeshNode(MeshRenderer& renderer, Mesh& mesh, ShaderProgram& program);
	AbstractMeshNode(const AbstractMeshNode& orig);
	virtual ~AbstractMeshNode();
	virtual void render(glm::mat4 base);
	
	GLuint getVAO() const {
		return vao;
	}
	
	ShaderProgram& getProgram() const {
		return program;
	}
};

#endif	/* SCENEGRAPH_ABSTRACTMESHNODE_HPP */

