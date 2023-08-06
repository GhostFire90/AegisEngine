#pragma once

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
	class AEGIS_API BaseSystem {
	public:
		BaseSystem(const char* name);
		virtual ~BaseSystem() = 0;
		virtual void Update(float dt) = 0;

		const std::string& GetName();
	protected:
		std::string* name;
	};
}