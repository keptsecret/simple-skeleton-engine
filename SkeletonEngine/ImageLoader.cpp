#include "ImageLoader.h"

#include "SkellyErrors.h"
#include "IOManager.h"
#include "picoPNG.h"

namespace SkeletonEngine
{

	GLTexture ImageLoader::loadPNG(std::string file_path)
	{
		GLTexture texture{};

		std::vector<unsigned char> in;
		if (IOManager::readFileToBuffer(file_path, in) == false)
		{
			fatalError("Failed to load PNG file to buffer!");
		}

		std::vector<unsigned char> out;
		unsigned long width, height;

		int error = decodePNG(out, width, height, &(in[0]), in.size());
		if (error != 0)
		{
			fatalError("decodePNG failed with error: " + std::to_string(error));
		}

		glGenTextures(1, &(texture.id));
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		// set some parameters on how to draw the texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);			// unbinds texture

		texture.width = static_cast<int>(width);
		texture.height = static_cast<int>(height);

		return texture;
	}

}
