#include "MngrModel.h"


MngrModel::MngrModel(const char * sceneFilename)
{
	LOG(INFO) << "MngrModel::MngrModel()";
	this->sceneFilename = sceneFilename;
}

MngrModel::~MngrModel()
{
	LOG(INFO) << "MngrModel::~MngrModel()";
}

void MngrModel::load()
{
	LOG(INFO) << "MngrModel::load()";

	std::string line;
	std::ifstream file(this->sceneFilename);

	while (std::getline(file, line))
	{
		if (line.substr(0, 1) == "M")
		{
			std::stringstream ss(line);
			std::vector<std::string> result;

			while (ss.good())
			{
				std::string substr;
				getline(ss, substr, ',');
				result.push_back(substr);
			}

			LdrModelObj ldrModelObj = LdrModelObj(result[2].c_str());

			this->models[std::stoi(result[1])] = ldrModelObj.getMeshes();
		}
	}
}

std::vector<Mesh> MngrModel::getModel(unsigned int id)
{
	return this->models[id];
}
