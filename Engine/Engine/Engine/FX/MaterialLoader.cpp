#include "MaterialLoader.h"


void MaterialLoader::LoadMaterial(std::string file_){
	std::ifstream in(file_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + file_, __FILE__, __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(matName, m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
		}
		//NS - Shininess
		if (line.substr(0, 4) == "\tNs ") {
			std::istringstream ns(line.substr(4));
			double x;
			ns >> x;
			m.shininess = x;
		}

		//D - Transparency
		if (line.substr(0, 3) == "\td ") {
			std::istringstream d(line.substr(3));
			double x;
			d >> x;
			m.transparency = x;
		}
		//KA - Ambient
		if (line.substr(0, 4) == "\tKa ") {
			std::istringstream ka(line.substr(4));
			double x, y, z;
			ka >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
		}
		//KD = Diffuse
		if (line.substr(0, 4) == "\tKd ") {
			std::istringstream kd(line.substr(4));
			double x, y, z;
			kd >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
		}
		//KS - Specular
		if (line.substr(0, 4) == "\tKs ") {
			std::istringstream ks(line.substr(4));
			double x, y, z;
			ks >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
		}

	}
	if (m.diffuseMap != 0){
		MaterialHandler::GetInstance()->AddMaterial(matName, m);
	}
}

GLuint MaterialLoader::LoadTexture(std::string fileName_){
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}


