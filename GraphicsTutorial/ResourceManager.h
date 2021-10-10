#pragma once
#include "TextureCache.h"

class ResourceManager
{
public:
	static GLTexture getTexture(const std::string& texture_path);

private:
	static TextureCache texture_cache_;
};

