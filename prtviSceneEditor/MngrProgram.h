#ifndef MNGR_PROGRAM_H
#define MNGR_PROGRAM_H

#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "vendor/easylogging++.h"

class MngrProgram
{
public:
	MngrProgram(const char* sceneFilename);
	~MngrProgram();
	void load();
private:
	std::map<int, Shader*> programs;
	const char* sceneFilename;
};

#endif // !MNGR_PROGRAM_H