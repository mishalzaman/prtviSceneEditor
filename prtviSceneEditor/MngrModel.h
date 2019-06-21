#ifndef MNGR_MODEL_H
#define MNGR_MODEL_H

#include "LdrModelObj.h"
#include <map>
#include <vector>
#include "Mesh.h"
#include "vendor/easylogging++.h"

class MngrModel
{
public:
	MngrModel(const char* sceneFilename);
	~MngrModel();
	void load();
	std::vector<Mesh> getModel(unsigned int id);
private:
	const char* sceneFilename;
	std::map<int, std::vector<Mesh>> models;
};

#endif
