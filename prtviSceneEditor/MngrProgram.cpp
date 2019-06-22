#include "MngrProgram.h"
#include <iostream>


MngrProgram::MngrProgram(const char* sceneFilename)
{
	LOG(INFO) << "MngrProgram::MngrProgram()";
	this->sceneFilename = sceneFilename;
}

MngrProgram::~MngrProgram()
{
	LOG(INFO) << "MngrProgram::~MngrProgram()";

	for (auto const& x : this->programs)
	{
		delete(x.second);
	}
}

void MngrProgram::load()
{
	LOG(INFO) << "MngrProgram::load()";

	std::string line;
	std::ifstream file(this->sceneFilename);

	while (std::getline(file, line))
	{
		if (line.substr(0, 1) == "P")
		{
			std::stringstream ss(line);
			std::vector<std::string> result;

			while (ss.good())
			{
				std::string substr;
				getline(ss, substr, ',');
				result.push_back(substr);
			}
			Shader* shader = new Shader{ result[2].c_str(), result[3].c_str() };
			this->programs[std::stoi(result[1])] = shader;
		}
	}
}

Shader * MngrProgram::getProgram(int id)
{
	return this->programs[id];
}
