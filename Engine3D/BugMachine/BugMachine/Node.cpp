#include "Node.h"
#include <d3dx9.h>

Node::Node(){}

void Node::updateBV(){

}

void Node::draw(Renderer& rkRenderer, CollisionResult eParentResult, Frustum& rkFrustum){
	updateWordTransformation();
	std::vector<Entity3D*>::iterator it;
	if (eParentResult != AllOutside)
	{
		if (eParentResult == AllInside)
		{
			for (it = _childs.begin(); it != _childs.end(); it++){
				(*it)->draw(rkRenderer, eParentResult, rkFrustum);
			}
		}
		else
		{
			if (rkFrustum.CheckCollision(BV) != AllOutside)
			{
				for (it = _childs.begin(); it != _childs.end(); it++){
					(*it)->draw(rkRenderer, rkFrustum.CheckCollision(BV), rkFrustum);
				}
			}
		}
	}
}

void Node::AddChild(Entity3D* child){
	child->setParent(*this);
	_childs.push_back(child);
}

void Node::updateWordTransformation(){
	Entity3D::updateWordTransformation();

	std::vector<Entity3D*>::iterator it;
	for (it = _childs.begin(); it != _childs.end(); it++){
		(*it)->updateWordTransformation();
	}
}

void Node::removeChild(Entity3D* child){
	std::vector<Entity3D*>::iterator it;
	it = std::find(_childs.begin(), _childs.end(), child);

	if (it != _childs.end()){
		child->_parent = NULL;
		_childs.erase(it);
	}
}