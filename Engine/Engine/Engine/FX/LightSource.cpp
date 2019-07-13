#include "LightSource.h"



LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 lightcolour_){
	SetPosition(position_);
	SetAmbient(ambient_);
	SetDiffuse(diffuse_);
	SetLightColour(lightcolour_);

}


LightSource::~LightSource(){

}

glm::vec3 LightSource::GetPosition() const{

	
	return position;
}

float LightSource::GetAmbient() const{

	
	return ambient;
}

float LightSource::GetDiffuse() const{

	
	return diffuse;
}

glm::vec3 LightSource::GetLightColour() const{
	
	return lightcolour;
}

void LightSource::SetPosition(glm::vec3 position_){
	position = position_;
}

void LightSource::SetAmbient(float ambient_){
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_){
	diffuse = diffuse_;
}

void LightSource::SetLightColour(glm::vec3 lightcolour_){
	lightcolour = lightcolour_;
}
