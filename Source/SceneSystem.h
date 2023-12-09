#pragma once
#include "BaseSystem.h"

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
	class Scene;
	class CameraComponent;
	class AEGIS_API SceneSystem : public BaseSystem {
	public:
		SceneSystem();
		~SceneSystem();
		
		void Update(float dt) override;
		
		void SetNextScene(Scene* nextScene);
		void RestartScene();

		static SceneSystem* GetSceneSystem();
		CameraComponent* GetActiveCamera() const;
	private:
		Scene *currentScene, *nextScene;
		bool isChanging;

	};
}