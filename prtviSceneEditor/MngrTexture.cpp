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
			std::stringstream ss(line);
			std::vector<std::string> result;

			while (ss.good())
			{
				std::string substr;
				getline(ss, substr, ',');
				result.push_back(substr);
			}

			LdrTexture texture = LdrTexture(result[2].c_str());
			texture.generate();

			this->textures[std::stoi(result[1])] = texture.getTexture();
		}
	}
}

textureData MngrTexture::getTexture(int id)
{
	return this->textures[id];
}
