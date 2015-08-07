/* 
 * File:   RenderObject.hpp
 * Author: Ale Strooisma
 *
 * Created on June 13, 2015, 5:42 PM
 */

#ifndef SCENEGRAPH_NODE_HPP
#define	SCENEGRAPH_NODE_HPP
#include <list>
#include <glm/fwd.hpp>

class Node {
private:
	Node* parent = nullptr;
	std::list<Node*> children;
public:
	Node();
	Node(const Node& orig);
	virtual ~Node();
	virtual void render(glm::mat4 base) = 0;
	virtual void renderAll(glm::mat4 base);
	void setParent(Node*);
	void removeFromTree();
	void addChild(Node*);
	void removeChild(Node*);
	Node* getParent() const;
	std::list<Node*>& getChildren();
};

#endif	/* SCENEGRAPH_NODE_HPP */

