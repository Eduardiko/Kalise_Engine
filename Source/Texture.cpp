#include "Texture.h"

#include "Globals.h"

#include "glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

Texture::Texture(bool active)
{
	id = -1;
	textureBuffer = -1;

	format = -1;
	formatUnsigned = -1;

	data = nullptr;
	
	width = -1;
	height = -1;
	
	name = "defaultTex";
	path = "Assets/Textures/";
}

Texture::Texture(uint id_, uint textureBuffer_, int format_, uint formatUnsigned_, GLubyte* data_, int width_, int height_, std::string name_, std::string path_)
{
	id = id_;
	textureBuffer = textureBuffer_;

	format = format_;
	formatUnsigned = formatUnsigned_;

	data = data_;

	width = width_;
	height = height_;

	name = name_;
	path = path_;
}

Texture::~Texture()
{
	name.clear();
	path.clear();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteBuffers(1, &textureBuffer);
	glDeleteTextures(1, &id);

	data = nullptr;

}

bool Texture::SetTexture(Texture* texture)
{
	if (texture != nullptr && texture->data != nullptr)
	{
		name = texture->name;
		path = texture->path;
		id = texture->id;
		format = texture->format;
		formatUnsigned = texture->formatUnsigned;
		width = texture->width;
		height = texture->height;

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, formatUnsigned, GL_UNSIGNED_BYTE, texture->data);

		//glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		data = texture->data;
		return true;
	}

	return false;
}
