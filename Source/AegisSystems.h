#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <unordered_map>


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

struct GLFWwindow;

namespace Aegis {
	class BaseSystem;
	

	enum class AEGIS_API WindowMode {
		Windowed,
		Borderless,
		Fullscreen
	};

	class AEGIS_API AegisSystems {
	public:
		
		~AegisSystems();		

		static void BeginLoop(void);

		static void Initialize(int width, int height, std::string title);

		static void SetClearColor(glm::vec3 color);

		static void AddSystem(BaseSystem* system);
		static BaseSystem* GetSystem(std::string name);

		static GLFWwindow* GetWindow();

		static AegisSystems* GetAegisSystems();
		static float GetTime();

		static bool GetKey(int key);
		static bool GetKeyTriggered(int key);
		static bool GetKeyReleased(int key);
		static const glm::vec2* GetMousePosition();

		static void SetWindowName(std::string name);

		static void Exit(void);
		static void SetWindowMode(WindowMode mode);

		static void GetWindowDimensions(int* width, int* height);

		friend void inputCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
		friend void mouseCallback(GLFWwindow* w, double x, double y);
		

	private:
		int Aegis_Init();
		int Aegis_SetupWindow(unsigned width, unsigned height);
		
		static GLFWwindow* window;
		static std::vector<BaseSystem*>* systems;
		static glm::vec3* clearColor;
		static glm::vec2* mousePosition;
		static glm::vec2* window_dimensions;

		AegisSystems(unsigned int width, unsigned int height, std::string name);
		
	};

	

	

	
}
