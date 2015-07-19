/* 
 * File:   Spatial.cpp
 * Author: Ale Strooisma
 * 
 * Created on July 19, 2015, 3:39 PM
 */

#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Spatial.hpp"
#include "../GameObject.hpp"

Spatial::Spatial(MeshRenderer& renderer, Mesh& mesh, ShaderProgram& program, GameObject& obj)
: AbstractMeshNode(renderer, mesh, program), obj(obj) {

}

Spatial::Spatial(const Spatial& orig) : AbstractMeshNode(orig), obj(obj) {
}

Spatial::~Spatial() {
}

void Spatial::render(glm::mat4 base) {
	AbstractMeshNode::render(
			glm::translate(base, obj.getPosition()) * glm::mat4_cast(obj.getOrientation()));
}
