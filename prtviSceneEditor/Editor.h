#ifndef EDITOR_H
#define EDITOR_H

class Editor
{
public:
	Editor(unsigned int width, unsigned int height);
	~Editor();
	void load(const char* sceneFilename);
	bool quit = false;
private:
	const char* sceneFilename;
};

#endif