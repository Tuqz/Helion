/* 
 * File:   SceneGraph.hpp
 * Author: Ale Strooisma
 *
 * Created on June 15, 2015, 5:31 PM
 */

#ifndef SCENEGRAPH_HPP
#define	SCENEGRAPH_HPP

#include "Node.hpp"


class SceneGraph : public Node {
public:
	SceneGraph();
	SceneGraph(const SceneGraph& orig);
	virtual ~SceneGraph();
	void render(glm::mat4 base);
	void renderAll(glm::mat4 base);
private:

};

#endif	/* SCENEGRAPH_HPP */

