#include "Texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <cerrno>
#include <string>

namespace Aegis {
	Image::Image(const char* path)
	{
		data = stbi_load(path, &dims.x, &dims.y, &channels, 0);
		if (!data) {
			char errstr[512];
			strerror_s(errstr, 512, errno);
			std::cerr << "Failed to load file " << path << ": " << errstr << '\n';
		}
	}
	glm::i32vec2 Image::GetDim()
	{
		return dims;
	}
	int Image::GetChannels()
	{
		return channels;
	}
	const unsigned char* Image::GetData()
	{
		return data;
	}
	Image::~Image()
	{
		stbi_image_free(data);
	}
	Texture::Texture(Image source)
	{
		glm::i32vec2 dims = source.GetDim();

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dims.x, dims.y, 0, GL_RGB, GL_UNSIGNED_BYTE, source.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	Texture::Texture(const char* path)
	{
		Image source = Image(path);

		glm::i32vec2 dims = source.GetDim();

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dims.x, dims.y, 0, GL_RGB, GL_UNSIGNED_BYTE, source.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	void Texture::Use()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
}