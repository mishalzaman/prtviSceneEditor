#include "LdrTexture.h"

LdrTexture::LdrTexture(const char * filename)
{
	this->filename = filename;
}

LdrTexture::~LdrTexture()
{
}

textureData LdrTexture::getTexture()
{
	return this->data;
}

bool LdrTexture::generate()
{
	glGenTextures(1, &this->data.texture);
	glBindTexture(GL_TEXTURE_2D, this->data.texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *data = stbi_load(this->filename, &this->data.width, &this->data.height, &this->data.nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->data.width, this->data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		return true;
	}
	else
	{
		LOG(ERROR) << "LdrTexture::generateTexture() Error loading texture";
		return false;
	}
	stbi_image_free(data);
}
