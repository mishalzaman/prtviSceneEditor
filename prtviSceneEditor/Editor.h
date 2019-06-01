#ifndef EDITOR_H
#define EDITOR_H

class Scene;

class Editor
{
public:
	Editor(unsigned int width, unsigned int height);
	~Editor();
	void load(const char* sceneFilename);
	bool quit = false;
private:
	const char* sceneFilename;
	Scene* scene;
	unsigned int width;
	unsigned int height;
};

#endif