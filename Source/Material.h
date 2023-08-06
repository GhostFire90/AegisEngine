#pragma once

/*
* For documentation purposes:
* Usage:
* A material is created first as a prefab material with the constructor and is instantiated using the copy constructor, or the instantiate function
* Instantiated materials can also be instantiated as if also a prefab, but to save computation on serialization, they function seperately
* 
* ShaderSources hold the compiled source code of the shader pre-linkage, shaders are linked programs of the ShaderSource, it is done this way for separate uniforms 
* 
* Terminology:
* "Real" - Meaning it is a usable material to render with
*/

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
#define EXPORT
#define IMPORT
#endif // _MSC_VER


#ifdef AEGIS_DLL_BUILD
#define AEGIS_API EXPORT
#else
#define AEGIS_API IMPORT
#endif // !AEGIS_DLL_BUILD

#include <map>
#include <string>
namespace Aegis {
	class ShaderSource;
	class Shader;
	class Texture;
	class AEGIS_API Material {
	public:
		/// <summary>
		/// Creates a material prefab
		/// </summary>
		/// <param name="name">name of the material</param>
		/// <param name="shader">shader source to be used</param>
		Material(const char* name, const ShaderSource& shader);

		/// <summary>
		/// Copy constructor, also serves as making materials "Real"
		/// </summary>
		/// <param name="other">the one to copy from</param>
		Material(const Material& other);

		/// <summary>
		/// Destructor, frees the shader if is "Real"
		/// </summary>
		~Material();

		/// <summary>
		/// wrapper around the copyconstructor
		/// </summary>
		/// <returns>a pointer to a newly allocated "Real" material</returns>
		Material* Instantiate() const;

		/// <summary>
		/// Gets the shader, usually for setting uniforms
		/// </summary>
		/// <returns>Pointer to the shader</returns>
		Shader* GetShader();

		/// <summary>
		/// Sets the texture to use
		/// </summary>
		/// <param name="tex">pointer to the texture</param>
		/// <param name="id">0-15, which tex to use</param>
		void SetTexture(const Texture* tex, unsigned int id);

		/// <summary>
		/// Renders using the material
		/// </summary>
		void Use();

		Material& operator=(const Material& rhs) = delete;

		
	private:
		const ShaderSource& source;
		Shader* shader;
		const char* name;
		unsigned int uniformCount;
		std::string** uniforms;
		std::map<std::string*, unsigned int>* uniformTypes;
		
		const Texture* textures[16];
	};
}