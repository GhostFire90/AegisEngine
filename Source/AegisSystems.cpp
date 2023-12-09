#include <glad/glad.h>
#include "AegisSystems.h"

#include <glfw3.h>
#include <exception>
#include <iostream>
#include "SceneSystem.h"
#include "BaseSystem.h"
#include <algorithm>





namespace Aegis {
	AegisSystems* as = nullptr;
	glm::vec3* AegisSystems::clearColor;
	std::unordered_map<int, bool> repeat_keys;
	glm::vec2* AegisSystems::mousePosition;
	GLFWwindow* AegisSystems::window;
	std::vector<BaseSystem*>* AegisSystems::systems;
	glm::vec2* AegisSystems::window_dimensions;

	glm::vec2 windowed_dimensions;

	std::unordered_map<int, bool> triggeredKeys;
	std::unordered_map<int, bool> releasedKeys;


	void inputCallback(GLFWwindow* win, int key, int scancode, int action, int mods) {
		
		triggeredKeys[key] = false;
		releasedKeys[key] = false;
		if (action == GLFW_PRESS) {
			if (!(repeat_keys)[key]) {
				
				triggeredKeys[key] = true;
				//std::cout << "Repeating: " << repeat_keys[key] << " Triggered:" << triggeredKeys[key] << "\n";
			}
				
			//releasedKeys[key] = false;
			(repeat_keys)[key] = true;
		}
		if (action == GLFW_RELEASE){
			//triggeredKeys[key] = false;
			releasedKeys[key] = true;
			(repeat_keys)[key] = false;
		}
		
	}

	void AegisSystems::GetWindowDimensions(int* width, int* height)
	{
		glm::i32vec2 windim;
		glfwGetWindowSize(AegisSystems::GetAegisSystems()->GetWindow(), &windim.x, &windim.y);
		*width = windim.x;
		*height = windim.y;
	}

	void sizeCallback(GLFWwindow* win, int, int) {

		
	}


	void mouseCallback(GLFWwindow* w, double x, double y) {
		*AegisSystems::mousePosition = glm::vec2(x, y);
	}

	void AegisSystems::Initialize(int width, int height, std::string title)
	{
		as = new AegisSystems(width, height, title);
	}

	AegisSystems::AegisSystems(unsigned int width, unsigned int height, std::string name)
	{
		if (as != nullptr) {
			return;
		}
		if (Aegis_Init() == -1) {
			throw std::string("Failed to initialize Aegis");
		}
		if (Aegis_SetupWindow(width, height) == -1) {
			throw std::string("Failed to initialize Aegis");
		}
		glEnable(GL_DEPTH_TEST);
		
		glfwSetKeyCallback(window, inputCallback);
		glfwSetCursorPosCallback(window, mouseCallback);

		window_dimensions = new glm::vec2(width, height);
		windowed_dimensions = *window_dimensions;

		clearColor = new glm::vec3();
		systems = new std::vector<BaseSystem*>;
		mousePosition = new glm::vec2();

		


		
		SetWindowName(name);
		
	}

	AegisSystems::~AegisSystems()
	{
	}


	int AegisSystems::Aegis_Init() {
		std::cout << "Initializing Aegis\n";
		if (glfwInit() == GLFW_FALSE) {
			std::cout << "Failed to initialize GLFW\n";
			return -1;
		}


		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		glfwWindowHint(GLFW_RESIZABLE, 0);

		glfwSetTime(0);

		window = nullptr;


		return 0;
	}

	int AegisSystems::Aegis_SetupWindow(unsigned width, unsigned height)
	{

		window = glfwCreateWindow(width, height, "", nullptr, nullptr);

		if (!window) {
			std::cout << "Failed to create window\n";
			Exit();
			return -1;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD\n";
			Exit();
			return -1;
		}

		glViewport(0, 0, width, height);
		return 0;
	}

	void AegisSystems::BeginLoop(void)
	{
		float oldTime;
		float time = 0;
		
		
		float dt;
		glfwMakeContextCurrent(window);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			if (GetKeyTriggered(GLFW_KEY_ESCAPE)) {
				SceneSystem* scenesys = (SceneSystem*)as->GetSystem("SceneSystem");
				if (scenesys != nullptr) {
					scenesys->SetNextScene(nullptr);
				}
				else {
					Exit();
				}
				
				//break;
			}

			oldTime = time;
			time = (float)glfwGetTime();

			dt = time - oldTime;
			

			glClearColor(clearColor->r, clearColor->g, clearColor->b, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (auto itr = systems->begin(); itr != systems->end(); itr++) {
				(*itr)->Update(dt);
			}
			
			
			triggeredKeys.clear();
			releasedKeys.clear();
			
			glfwSwapBuffers(window);
			
		}
		delete clearColor;

		delete systems;
		delete mousePosition;
		delete window_dimensions;
		glfwDestroyWindow(window);
		glfwTerminate();
		delete as;
		
	}

	void AegisSystems::Exit(void) {
		std::cout << "Exiting Aegis\n";
		glfwSetWindowShouldClose(window, 1);
		for (auto itr = systems->begin(); itr != systems->end(); itr++) {
			if (*itr) {
				delete (*itr);
				*itr = nullptr;
				//systems.erase(itr);
			}
			
		}		
		return;
	}

	void AegisSystems::SetWindowMode(WindowMode mode)
	{
		GLFWmonitor* m = glfwGetPrimaryMonitor();
		const GLFWvidmode* vm = glfwGetVideoMode(m);
		switch (mode)
		{
		case Aegis::WindowMode::Windowed:
			glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
			glfwSetWindowAttrib(window, GLFW_FLOATING, GLFW_FALSE);
			
			*window_dimensions = windowed_dimensions;
			glfwSetWindowSize(window, window_dimensions->x, window_dimensions->y);
			break;
		case Aegis::WindowMode::Borderless:
		{
			glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
			//glfwSetWindowMonitor(window, nullptr, 0, 0, vm->width, vm->height, 60);	
			glfwSetWindowSize(window, vm->width, vm->height);
			glfwSetWindowPos(window, 0, 0);
			window_dimensions->x = vm->width;
			window_dimensions->y = vm->height;

		}
			break;
		case Aegis::WindowMode::Fullscreen:
		{
			glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
			glfwSetWindowAttrib(window, GLFW_FLOATING, GLFW_FALSE);
			glfwSetWindowMonitor(window, m, 0, 0, vm->width, vm->height, vm->refreshRate);
			window_dimensions->x = vm->width;
			window_dimensions->y = vm->height;

		}
			break;
		default:
			break;
		}
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

	void AegisSystems::SetClearColor(glm::vec3 color)
	{
		*clearColor = color;
	}

	void AegisSystems::AddSystem(BaseSystem* system)
	{
		systems->push_back(system);
	}

	Aegis::BaseSystem* AegisSystems::GetSystem(std::string name)
	{
		auto itr = std::find_if(systems->begin(), systems->end(), [name](BaseSystem* sys) {
			return name.compare(sys->GetName()) == 0;
			});
		if (itr != systems->end()) {
			return *itr;
		}
		return nullptr;
	}

	GLFWwindow* AegisSystems::GetWindow()
	{
		return window;
	}
	AegisSystems* AegisSystems::GetAegisSystems()
	{
		return as;
	}
	float AegisSystems::GetTime()
	{
		return (float)glfwGetTime();
	}
	bool AegisSystems::GetKey(int key)
	{
		return (repeat_keys)[key];
	}
	bool AegisSystems::GetKeyTriggered(int key)
	{
		auto stat = glfwGetKey(window, key);

		if (triggeredKeys[key]) {
			//std::cout << "Triggered\n";
			
			return true;
		}

		return false;
		
	}
	bool AegisSystems::GetKeyReleased(int key)
	{
		if (releasedKeys[key]) {
			
			return true;
		}
		return false;
	}
	const glm::vec2* AegisSystems::GetMousePosition()
	{
		return mousePosition;
	}
	void AegisSystems::SetWindowName(std::string name)
	{
		glfwSetWindowTitle(window, name.c_str());
	}
	
	
}


