#ifndef MNGR_TEXTURE
#define MNGR_TEXTURE

#include "LdrTexture.h"
#include "vendor/easylogging++.h"
#include <map>

class MngrTexture
{
public:
	MngrTexture(const char* sceneFilename);
	~MngrTexture();
	void load();
	textureData getTexture(int id);
private:
	const char* sceneFilename;
	std::map<int, textureData> textures;
};

#endif