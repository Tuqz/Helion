/* 
 * File:   Spatial.hpp
 * Author: Ale Strooisma
 *
 * Created on July 19, 2015, 3:39 PM
 */

#ifndef SPATIAL_HPP
#define	SPATIAL_HPP

#include "AbstractMeshNode.hpp"
class GameObject;

class Spatial : public AbstractMeshNode {
private:
	GameObject& obj;
	float scale = 1;
public:
	Spatial(MeshRenderer& renderer, Mesh& mesh, GameObject& obj);
	Spatial(const Spatial& orig);
	virtual ~Spatial();
	virtual void render(glm::mat4 base);
	float getScale() const {
		return scale;
	}
	void setScale(float scale) {
		this->scale = scale;
	}
};

#endif	/* SPATIAL_HPP */

