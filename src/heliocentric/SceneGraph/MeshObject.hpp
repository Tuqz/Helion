/* 
 * File:   MeshObject.hpp
 * Author: Ale Strooisma
 *
 * Created on June 15, 2015, 5:40 PM
 */

#ifndef MESHOBJECT_HPP
#define	MESHOBJECT_HPP

#include "RenderObject.hpp"
class Mesh;

class MeshObject : public RenderObject {
private:
	GLuint& vao;
	Mesh& mesh;
public:
	MeshObject(Mesh& mesh, GLuint& vao);
	MeshObject(const MeshObject& orig);
	virtual ~MeshObject();
	virtual void render();
};

#endif	/* MESHOBJECT_HPP */

