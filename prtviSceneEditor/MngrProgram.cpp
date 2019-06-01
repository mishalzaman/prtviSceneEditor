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

	while (std::getline(file, line, ','))
	{
		if (line.substr(0, 1) == "P")
		{
			std::istringstream iss(line);
			std::string ignore;
			int id;
			std::string vertex, fragment;

			iss >> ignore >> id >> vertex >> fragment;
			Shader* shader = new Shader{ vertex.c_str(), fragment.c_str() };
			
			this->programs[id] = shader;
		}
	}
}

Shader * MngrProgram::getProgram(int id)
{
	return this->programs[id];
}
