#pragma once

#include <glm/vec4.hpp>

#ifdef AEGIS_DLL_BUILD
#define AEGIS_API __declspec(dllexport)
#else
#define AEGIS_API __declspec(dllimport)
#endif // !AEGIS_DLL_BUILD

namespace Aegis {
	class AEGIS_API Scene {
	public:
		Scene();
		virtual ~Scene() = 0;
		
		virtual void Load() = 0;
		virtual void Init() = 0;

		virtual void Update(float dt) = 0;
		
		virtual void Exit() = 0;
		virtual void Unload() = 0;
	protected:
		glm::vec4* ambientLightColor;
	};
}