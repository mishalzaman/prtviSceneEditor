#ifndef LDR_TEXTURE
#define LDR_TEXTURE

#include <GL/glew.h>
#include "vendor/stb_image.h"
#include "vendor/easylogging++.h"

struct textureData
{
	unsigned int texture;
	int width;
	int height;
	int nrChannels;
};

class LdrTexture
{
public:
	LdrTexture(const char* filename);
	~LdrTexture();
	textureData getTexture();
	bool generate();
private:
	textureData data;
	const char* filename;
};

#endif LDR_TEXTURE
