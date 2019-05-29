#include "Editor.h"
#include "vendor/easylogging++.h"

Editor::Editor(unsigned int width, unsigned int height)
{
	LOG(INFO) << "Editor::Editor()";
}


Editor::~Editor()
{
	LOG(INFO) << "Editor::~Editor()";
}

void Editor::load(const char* sceneFilename)
{
	LOG(INFO) << "Editor::load()";
	this->sceneFilename = sceneFilename;
}
