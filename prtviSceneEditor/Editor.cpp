#include "Editor.h"
#include "vendor/easylogging++.h"
#include "Scene.h"

Editor::Editor(unsigned int width, unsigned int height)
{
	LOG(INFO) << "Editor::Editor()";
	this->width = width;
	this->height = height;
}

Editor::~Editor()
{
	LOG(INFO) << "Editor::~Editor()";
	delete(this->scene);
}

void Editor::load(const char* sceneFilename)
{
	LOG(INFO) << "Editor::load()";
	this->sceneFilename = sceneFilename;
	this->scene = new Scene(this->width, this->height, this->sceneFilename);
	
	this->scene->load();
}
