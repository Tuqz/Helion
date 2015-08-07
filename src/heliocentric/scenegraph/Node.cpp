/* 
 * File:   RenderObject.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 13, 2015, 5:42 PM
 */

#include "Node.hpp"
#include <list>
#include <glm/mat4x4.hpp>

using namespace std;
typedef list<Node*>::iterator iter; 

Node::Node() {
}

Node::~Node() {
}

void Node::renderAll(glm::mat4 base) {
	render(base);
	for (iter it = children.begin(); it != children.end(); ++it) {
		(*it)->renderAll(base);
	}
}

void Node::setParent(Node* parent) {
	if (this->parent != nullptr) {
		removeFromTree();
	}
	if (parent != nullptr) {
		this->parent = parent;
		parent->addChild(this);
	}
}

void Node::removeFromTree() {
	Node* oldParent = parent;
	parent = nullptr;
	oldParent->removeChild(this);
}

void Node::addChild(Node* child) {
	if (child->parent == this) {
		children.push_back(child);
	} else {
		child->setParent(this);
	}
}

void Node::removeChild(Node* child) {
	if (child->getParent() != nullptr) {
		child->removeFromTree();
	} else {
		children.remove(child);
	}
}

Node* Node::getParent() const {
	return parent;
}

std::list<Node*>& Node::getChildren() {
	return children;
}
