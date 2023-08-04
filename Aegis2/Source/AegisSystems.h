#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>

#ifdef AEGIS_DLL_BUILD
#define AEGIS_API __declspec(dllexport)
#else
#define AEGIS_API __declspec(dllimport)
#endif // !AEGIS_DLL_BUILD

namespace Aegis {
	class BaseSystem;
	struct KeyState {
		KeyState(bool, bool);
		bool lastFrame;
		bool currentFrame;
	};

	class AEGIS_API AegisSystems {
	public:
		AegisSystems(unsigned int width, unsigned int height);
		~AegisSystems();		

		static void Aegis_BeginLoop(void);

		

		static void Aegis_SetClearColor(glm::vec3 color);

		static void Aegis_AddSystem(BaseSystem* system);
		BaseSystem* Aegis_GetSystem(std::string name);

		static GLFWwindow* GetWindow();

		static AegisSystems* GetAegisSystems();
		static float GetTime();

		static bool GetKey(int key);
		static bool GetKeyTriggered(int key);
		static bool GetKeyReleased(int key);
		static const glm::vec2* GetMousePosition();

		static void Aegis_Exit(void);

		friend void inputCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
		friend void mouseCallback(GLFWwindow* w, double x, double y);

	private:
		int Aegis_Init();
		int Aegis_SetupWindow(unsigned width, unsigned height);
		
		static GLFWwindow* window;
		static std::vector<BaseSystem*>* systems;
		static glm::vec3* clearColor;
		static glm::vec2* mousePosition;
		static AegisSystems* as;
		static std::map<int, KeyState>* keyStates; // 0
	};

	

	

	
}
