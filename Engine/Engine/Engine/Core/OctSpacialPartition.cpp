#include "OctSpacialPartition.h"

int OctNode::childNum = 0;

OctSpacialPartition::OctSpacialPartition(float worldSize_){
	root = new OctNode(glm::vec3(-(worldSize_ / 2.0f)), worldSize_, 0);
	root->Octify(3);
	std::cout << "There are " << root->GetChildCount() << " child nodes" << std::endl;
}


void OctSpacialPartition::AddObjectToCell(OctNode * cell_, GameObject * obj_){

}

void OctSpacialPartition::PrepareCollisionQuery(OctNode * cell_, Ray ray_){

}

OctSpacialPartition::~OctSpacialPartition(){
	delete root;
	root = nullptr;

	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList){
			cell= nullptr;
		}
		rayIntersectionList.clear();
		rayIntersectionList.shrink_to_fit();
	}
}

void OctSpacialPartition::AddObject(GameObject * obj_){
	AddObjectToCell(root, obj_);
}

GameObject * OctSpacialPartition::GetCollision(Ray ray_){
	rayIntersectionList.clear();
	PrepareCollisionQuery(root, ray_);
	GameObject* result = nullptr;
	float shortestDistance = FLT_MAX;
	for (auto c : rayIntersectionList) {
		for (auto go : c->objectList) {
			if (ray_.IsColliding(&go->GetBoundingBox())) {
				if (ray_.intersectionDistance < shortestDistance) {
					result = go;
					shortestDistance = ray_.intersectionDistance;
				}
			}
		}
		if (result != nullptr) {
			return result;
		}

	}
	return nullptr;
}

OctNode::OctNode(glm::vec3 position_, float size_, OctNode * parent_){
	octBounds = new BoundingBox();
	octBounds->minVert = position_;
	octBounds->maxVert = position_ + glm::vec3(size_);

	size = size_;

	for (int i = 0; i < 8; i++){
		children[i] = 0;
	}
	
	parent = parent_;

}

OctNode::~OctNode(){
	delete octBounds;
	octBounds = nullptr;

	if (objectList.size() > 0) {
		for (auto go : objectList) {
			go = nullptr;
		}
		objectList.clear();
		objectList.shrink_to_fit();
	}

	for (int i = 0; i < 8; i++) {
		if (children[i] != nullptr) {
			delete children[i];
			children[i] = nullptr;
		}
	}
}

void OctNode::Octify(int depth_){
	if (depth_ > 0 && this) {
		float half = size / 2.0f;
		children[OCT_TLF] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[OCT_BLF] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z + half), half, this);
		children[OCT_BRF] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z + half), half, this);
		children[OCT_TRF] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[OCT_TRR] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[OCT_TLR] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[OCT_BLR] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[OCT_BRR] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);


		//fill in the rear section

		childNum += 8;
	}

	if (depth_ > 0 && this) {
		for (int i = 0; i < 8; i++) {
			children[i]->Octify(depth_ - 1);
		}
	}
}

OctNode * OctNode::GetParent(){

	return parent;
}

OctNode * OctNode::GetChild(OctChildren type_){

	return children[type_];
}

void OctNode::AddCollisionObject(GameObject * obj_){
	objectList.push_back(obj_);
	std::cout << "Added " << obj_->GetTag() << " to cell: " << glm::to_string(octBounds->maxVert) << std::endl;
}

int OctNode::GetObjectCount() const{
	return objectList.size();
}

bool OctNode::isLeaf() const{
	if (children[0] == 0 || children[0] == nullptr) {
		return true;
	}
	return false;
}

BoundingBox * OctNode::GetBoundingBox() const{

	return octBounds;;
}

int OctNode::GetChildCount() const{

	return childNum;
}
