#include "Scene.h"
#include "SceneSystem.h"
#include "AegisSystems.h"
#include "ObjectManager.h"

namespace Aegis {
	SceneSystem::SceneSystem() : BaseSystem("SceneSystem"), currentScene(nullptr), nextScene(nullptr), isChanging(true)
	{
	}
	SceneSystem::~SceneSystem()
	{
	}
	void SceneSystem::Update(float dt)
	{
		if (isChanging) {
			ObjectManager* manager = (ObjectManager*)AegisSystems::GetAegisSystems()->GetSystem("ObjectManager");
			if (manager)
				manager->ClearManager();
			//exit if nextscene is null
			if (nextScene == nullptr) {
				if (currentScene) {
					currentScene->Exit();
					currentScene->Unload();
				}
				
				delete currentScene;
				AegisSystems* as = AegisSystems::GetAegisSystems();
				as->Exit();
				return;
			}
			//the scene is restarting if the next scene is the same as the current, dont waste time loading/unloading
			else if (nextScene == currentScene) {
				currentScene->Exit();
				currentScene->Init();
				nextScene = nullptr;
			}
			//else, exit the current scene, unload the current assets, load the new assets, initialize new scene, set current scene to the new one
			else {
				
				if (currentScene != nullptr) {
					currentScene->Exit();
					currentScene->Unload();
					delete currentScene;
				}
				
				nextScene->Load();
				nextScene->Init();

				currentScene = nextScene;
				nextScene = nullptr;
			}
			
			isChanging = false;
		}
		currentScene->Update(dt);
	}
	void SceneSystem::SetNextScene(Scene* _nextScene)
	{
		nextScene = _nextScene;
		isChanging = true;
	}
	void SceneSystem::RestartScene()
	{
		SetNextScene(currentScene);
	}
	SceneSystem* SceneSystem::GetSceneSystem()
	{
		return (SceneSystem*)AegisSystems::GetSystem("SceneSystem");
	}
	CameraComponent* SceneSystem::GetActiveCamera() const
	{
		return currentScene->camera;
	}
}