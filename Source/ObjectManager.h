#pragma once

#include "BaseSystem.h"
#include <vector>
#include <string>


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