#pragma once


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

namespace Aegis {
	class AEGIS_API ShaderSource {
	public:
		ShaderSource(const char* vertPath, const char* fragPath);
		~ShaderSource();

		friend class Shader;
	private:
		int vertShader, fragShader;

	};
}