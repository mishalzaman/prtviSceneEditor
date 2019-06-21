#include "Scene.h"

Scene::Scene(unsigned int width, unsigned int height, const char * filename):
	programs(filename),
	textures(filename),
	models(filename)
{
	LOG(INFO) << "Scene::Scene()";
	this->width = width;
	this->height = height;
	this->filename = filename;
}

void Scene::load()
{
	this->programs.load();
	this->textures.load();
	this->models.load();
}

Scene::~Scene()
{
	LOG(INFO) << "Scene::~Scene()";
}

Shader* Scene::findProgramById(int id)
{
	return this->programs.getProgram(id);
}
