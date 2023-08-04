#pragma once

#include <glm/vec2.hpp>

#ifdef AEGIS_DLL_BUILD
#define AEGIS_API __declspec(dllexport)
#else
#define AEGIS_API __declspec(dllimport)
#endif // !AEGIS_DLL_BUILD

namespace Aegis {
	class Image {
	public:
		Image(const char* path);
		glm::i32vec2 GetDim();
		int GetChannels();
		const unsigned char* GetData();
		~Image();
		friend class Texture;
	private:
		glm::i32vec2 dims;
		int channels;
		unsigned char* data;
	};
	class AEGIS_API Texture {
	public:
		Texture(Image source);
		Texture(const char* path);
		void Use();
		friend class Material;
	private:
		unsigned int id;
	};
}
