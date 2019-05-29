#include "MngrTexture.h"

MngrTexture::MngrTexture(const char* sceneFilename)
{
	LOG(INFO) << "MngrTexture::MngrTexture()";
	this->sceneFilename = sceneFilename;
}

MngrTexture::~MngrTexture()
{
	LOG(INFO) << "MngrTexture::~MngrTexture()";
}

void MngrTexture::load()
{
	LOG(INFO) << "MngrTexture::load()";

	std::string line;
	std::ifstream file(this->sceneFilename);

	while (std::getline(file, line))
	{
		if (line.substr(0, 1) == "T")
		{
			std::istringstream iss(line);
			std::string ignore;
			int id;
			std::string image;

			iss >> ignore >> id >> image;

			LdrTexture texture = LdrTexture(image.c_str());
			texture.generate();

			this->textures[id] = texture.getTexture();
		}
	}
}

textureData MngrTexture::getTexture(int id)
{
	return this->textures[id];
}
