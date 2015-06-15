/* 
 * File:   SceneGraph.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 15, 2015, 5:31 PM
 */

#include "SceneGraph.hpp"

using namespace std;

typedef list<RenderObject*>::iterator iter; 

SceneGraph::SceneGraph() {
}

SceneGraph::SceneGraph(const SceneGraph& orig) {
}

SceneGraph::~SceneGraph() {
}

void SceneGraph::render() {
	renderAll();
}

void SceneGraph::renderAll() {
	for (iter it = getChildren().begin(); it != getChildren().end(); ++it) {
		(*it)->renderAll();
	}
}