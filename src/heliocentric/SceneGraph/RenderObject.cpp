/* 
 * File:   RenderObject.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 13, 2015, 5:42 PM
 */

#include <list>
#include "RenderObject.hpp"

using namespace std;
typedef list<RenderObject*>::iterator iter; 

RenderObject::RenderObject() {
}

RenderObject::~RenderObject() {
}

void RenderObject::renderAll() {
	render();
	for (iter it = children.begin(); it != children.end(); ++it) {
		(*it)->renderAll();
	}
}

void RenderObject::setParent(RenderObject* parent) {
	if (this->parent != nullptr) {
		removeFromTree();
	}
	if (parent != nullptr) {
		this->parent = parent;
		parent->addChild(this);
	}
}

void RenderObject::removeFromTree() {
	RenderObject* oldParent = parent;
	parent = nullptr;
	oldParent->removeChild(this);
}

void RenderObject::addChild(RenderObject* child) {
	if (child->parent == this) {
		children.push_back(child);
	} else {
		child->setParent(this);
	}
}

void RenderObject::removeChild(RenderObject* child) {
	if (child->getParent() != nullptr) {
		child->removeFromTree();
	} else {
		children.remove(child);
	}
}

RenderObject* RenderObject::getParent() const {
	return parent;
}

std::list<RenderObject*>& RenderObject::getChildren() {
	return children;
}



