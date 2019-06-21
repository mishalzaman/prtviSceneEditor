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

	// TODO fix the file reader for comma delimeted files.
	// Apply to other manager classes.

	while (std::getline(file, line))
	{
		if (line.substr(0, 1) == "#")
		{
			continue;
		}

		if (line.substr(0, 1) == "M")
		{
			
			while (std::getline(file, line, ','))
			{
				LOG(INFO) << "MngrModel::load() | LINE: " << line;
			}
		}

		if (line.substr(0, 1) == "M")
		{
			
			std::istringstream iss(line);
			std::string ignore;
			int id;
			std::string filename;

			iss >> ignore >> id >> filename;

			LdrModelObj ldrModelObj = LdrModelObj(filename.c_str());

			this->models[id] = ldrModelObj.getMeshes();
			LOG(INFO) << "MngrModel::load() | Loaded " << filename;
		}
	}
}

std::vector<Mesh> MngrModel::getModel(unsigned int id)
{
	return this->models[id];
}
