#include "Square.h"



Square::Square(GLuint shaderProgram_, GLuint textureID_) : Model(shaderProgram_) {
	Vertex v;
	std::vector<Vertex> vertexlist;

	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexlist.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexlist.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexlist.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexlist.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexlist.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexlist.push_back(v);

	AddMesh(new Mesh(&vertexlist, textureID_, shaderProgram_));
}


Square::~Square() {

}
