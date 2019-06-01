#ifndef SCENE_H
#define SCENE_H

#include "vendor/easylogging++.h"
#include "MngrProgram.h"
#include "MngrTexture.h"

class Scene
{
public:
	Scene(unsigned int width, unsigned int height, const char* filename);
	void load();
	~Scene();
	Shader* findProgramById(int id);
private:
	const char* filename;
	unsigned int width;
	unsigned int height;
	MngrProgram programs;
	MngrTexture textures;
};

#endif

