#pragma once

#include <glm/vec4.hpp>

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
	class CameraComponent;
	class AEGIS_API Scene {
	public:
		Scene();
		virtual ~Scene() = 0;
		
		virtual void Load() = 0;
		virtual void Init() = 0;

		virtual void Update(float dt) = 0;
		
		virtual void Exit() = 0;
		virtual void Unload() = 0;
		CameraComponent* camera;
	protected:
		
		glm::vec4* ambientLightColor;
	};
}