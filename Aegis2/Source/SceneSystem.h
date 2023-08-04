#pragma once
#include "BaseSystem.h"

#ifdef AEGIS_DLL_BUILD
#define AEGIS_API __declspec(dllexport)
#else
#define AEGIS_API __declspec(dllimport)
#endif // !AEGIS_DLL_BUILD


namespace Aegis {
	class Scene;
	class AEGIS_API SceneSystem : public BaseSystem {
	public:
		SceneSystem();
		~SceneSystem();
		
		void Update(float dt) override;
		
		void SetNextScene(Scene* nextScene);
		void RestartScene();
	private:
		Scene *currentScene, *nextScene;
		bool isChanging;

	};
}