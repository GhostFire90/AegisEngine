#pragma once

#ifdef AEGIS_DLL_BUILD
#define AEGIS_API __declspec(dllexport)
#else
#define AEGIS_API __declspec(dllimport)
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