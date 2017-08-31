#pragma once

#include "Renderer.h"
#include "Texture_data.h"

struct Image_data
{
	GLuint Texture_ID;
	unsigned int height;
	unsigned int width;
};

class Texture_Cache
{
	private:
		map<string, Image_data> Texture_map;

	public:
		Texture_Cache();

		~Texture_Cache();

		Image_data getTexture(const string &texture_path);
};
