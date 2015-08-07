/* 
 * File:   SceneGraph.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 15, 2015, 5:31 PM
 */

#include "SceneGraph.hpp"
#include <glm/mat4x4.hpp>

using namespace std;

typedef list<Node*>::iterator iter; 

SceneGraph::SceneGraph() {
}

SceneGraph::SceneGraph(const SceneGraph& orig) {
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::render(glm::mat4 base) {
	renderAll(base);
}

void SceneGraph::renderAll(glm::mat4 base) {
	for (iter it = getChildren().begin(); it != getChildren().end(); ++it) {
		(*it)->renderAll(base);
	}
}