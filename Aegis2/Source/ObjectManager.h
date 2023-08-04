#pragma once

#include "BaseSystem.h"
#include <vector>
#include <string>

#ifdef AEGIS_DLL_BUILD
#define AEGIS_API __declspec(dllexport)
#else
#define AEGIS_API __declspec(dllimport)
#endif // !AEGIS_DLL_BUILD


namespace Aegis {
	class AegisObject;
	class CameraComponent;
	class AEGIS_API ObjectManager : public BaseSystem {
	public:
		ObjectManager();
		~ObjectManager();
		void Update(float dt) override;
		void AddObject(AegisObject* object);

		void SetActiveCamera(CameraComponent* camera);
		CameraComponent* GetActiveCamera() const;
		
		void ClearManager();

		static ObjectManager* GetObjectManager();

	private:
		std::vector<AegisObject*>* objects;
		CameraComponent* activeCam;
	};
}