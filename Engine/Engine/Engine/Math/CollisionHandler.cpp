#include "CollisionHandler.h"



std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::previousCollisions = std::vector<GameObject*>();

CollisionHandler::CollisionHandler(){
	
}


CollisionHandler::~CollisionHandler(){

}

CollisionHandler * CollisionHandler::GetInstance(){
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::Initialize(float worldSize_){
	previousCollisions.clear();
	previousCollisions.shrink_to_fit();
	
	scenePartition = new OctSpacialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject * go_){
	scenePartition->AddObject(go_);
}

void CollisionHandler::Update(glm::vec2 mousePosition_, int buttonType_){
	Ray collisionRay = CollisionDetection::ScreenToWorldRay(mousePosition_, Engine::GetInstance()->GetScreenSize());
	GameObject* hitResult = scenePartition->GetCollision(collisionRay);

	float minDistance = 999999999.0f;

	if (hitResult) {
		hitResult->SetHit(true, buttonType_);
	}

	for (auto c : previousCollisions) {
		if (hitResult != c && c != nullptr) {
			c->SetHit(false, buttonType_);
			c = nullptr;
		}
	}

	previousCollisions.clear();

	if (hitResult) {
		previousCollisions.push_back(hitResult);
	}

	/*for (int i = 0; i < colliders.size(); i++) {
		if (CollisionDetection::RayOBBIntersection(&collisionRay, &colliders[i]->GetBoundingBox())) {
			if (collisionRay.intersectionDistance <= minDistance) {
				minDistance = collisionRay.intersectionDistance;
				colliders[i]->SetHit(true, buttonType_);
			}
			for (int j = 0; j < previousCollisions.size(); j++) {
				if (previousCollisions[j] != colliders[i] && previousCollisions[j] != nullptr) {
					previousCollisions[j]->SetHit(false, buttonType_);
				}
			}

			previousCollisions.clear();
			previousCollisions.push_back(colliders[i]);
		}
	}*/
}
