#pragma once

#include <string>

#ifdef AEGIS_DLL_BUILD
#define AEGIS_API __declspec(dllexport)
#else
#define AEGIS_API __declspec(dllimport)
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