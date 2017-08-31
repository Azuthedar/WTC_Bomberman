#include "stdafx.h"
#include "Texture_Cache.h"
#include "Texture_loader.h"

Texture_Cache::Texture_Cache()
{
}


Texture_Cache::~Texture_Cache()
{
}

Image_data Texture_Cache::getTexture(const string & texture_path)
{
	//Creates Map iterator.
	map<string, Image_data>::iterator Val = Texture_map.find(texture_path);

	if (Texture_map.end() == Val)
	{
		Image_data new_texture = Texture_loader::LoadPNG(texture_path);

		pair<string, Image_data> new_insert(texture_path, new_texture);

		//can use make_pair();
		Texture_map.insert(new_insert);
		return (new_texture);
	}

	return (Val->second);
}
