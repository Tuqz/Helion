/* 
 * File:   SceneGraph.hpp
 * Author: Ale Strooisma
 *
 * Created on June 15, 2015, 5:31 PM
 */

#ifndef SCENEGRAPH_HPP
#define	SCENEGRAPH_HPP

#include "RenderObject.hpp"


class SceneGraph : public RenderObject {
public:
	SceneGraph();
	SceneGraph(const SceneGraph& orig);
	virtual ~SceneGraph();
	void render();
	void renderAll();
private:

};

#endif	/* SCENEGRAPH_HPP */

