#include "Node.h"

Node::Node(){}

void Node::draw(){
	std::vector<Entity3D*>::iterator it;
	it = _childs.begin();

	for (it = _childs.begin(); it != _childs.end(); it++){
		(*it)->draw();
	}
}

void Node::AddChild(Entity3D* child){
	_childs.push_back(child);
}

void Node::setParent(Node& parent){
	_parent = &parent;
}