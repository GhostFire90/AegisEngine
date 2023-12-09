#include "ObjectManager.h"
#include "BaseSystem.h"
#include "AegisObject.h"
#include "AegisSystems.h"
#include <iostream>

namespace Aegis {
	ObjectManager::ObjectManager() : BaseSystem("ObjectManager")
	{
		objects = new std::vector<AegisObject*>();
		activeCam = nullptr;
	}
	ObjectManager::~ObjectManager()
	{
		
		for (auto itr = objects->begin(); itr != objects->end(); itr++) {
			delete (*itr);
		}
		delete objects;
	}
	void ObjectManager::Update(float dt)
	{
		for (auto itr = objects->begin(); itr != objects->end(); itr++) {
			(*itr)->Update(dt);
		}
		for (auto itr = objects->begin(); itr != objects->end(); itr++) {
			(*itr)->Render(dt);
			if ((*itr)->GetDestroyed()) {
				delete (*itr);
				objects->erase(itr);
			}
		}
	}
	void ObjectManager::AddObject(AegisObject* object)
	{
		objects->push_back(object);
	}

	void ObjectManager::SetActiveCamera(CameraComponent* camera)
	{
		activeCam = camera;
	}

	

	void ObjectManager::ClearManager()
	{
		for (auto itr = objects->begin(); itr != objects->end();) {
			if ((*itr)->destroyOnLoad) {
				delete (*itr);
				itr = objects->erase(itr);
			}
			else {
				itr++;
			}
		}
	}

	ObjectManager* ObjectManager::GetObjectManager()
	{
		ObjectManager* man = (ObjectManager*)AegisSystems::GetAegisSystems()->GetSystem("ObjectManager");
		if (man != nullptr) {
			return man;
		}
		else {
			std::cout << "Could not find Object manager, did you add it to Aegis?\n";
			return nullptr;
		}
		
	}
}

