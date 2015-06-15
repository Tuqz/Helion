/* 
 * File:   RenderObject.hpp
 * Author: Ale Strooisma
 *
 * Created on June 13, 2015, 5:42 PM
 */

#ifndef RENDEROBJECT_HPP
#define	RENDEROBJECT_HPP
#include <list>

class RenderObject {
private:
	RenderObject* parent = nullptr;
	std::list<RenderObject*> children;
public:
	RenderObject();
	RenderObject(const RenderObject& orig);
	virtual ~RenderObject();
	virtual void render() = 0;
	virtual void renderAll();
	void setParent(RenderObject*);
	void removeFromTree();
	void addChild(RenderObject*);
	void removeChild(RenderObject*);
	RenderObject* getParent() const;
	std::list<RenderObject*>& getChildren();
};

#endif	/* RENDEROBJECT_HPP */

