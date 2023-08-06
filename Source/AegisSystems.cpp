#include <glad/glad.h>
#include "AegisSystems.h"

#include <glfw3.h>
#include <exception>
#include <iostream>
#include "SceneSystem.h"
#include "BaseSystem.h"
#include <algorithm>





namespace Aegis {
	AegisSystems* AegisSystems::as = nullptr;
	glm::vec3* AegisSystems::clearColor;
	std::map<int, KeyState>* AegisSystems::keyStates;
	glm::vec2* AegisSystems::mousePosition;
	GLFWwindow* AegisSystems::window;
	std::vector<BaseSystem*>* AegisSystems::systems;

	void inputCallback(GLFWwindow* win, int key, int scancode, int action, int mods) {
		auto itr = AegisSystems::keyStates->find(key);
		if (itr == AegisSystems::keyStates->end()) {
			itr = AegisSystems::keyStates->insert(std::make_pair(key, KeyState(false, false))).first;
		}
		KeyState state = (*itr).second;
		switch (action) {
		case GLFW_PRESS:
			state.currentFrame = true;
			state.lastFrame = false;
			break;
		case GLFW_REPEAT:
			state.currentFrame = true;
			state.lastFrame = true;
			break;
		case GLFW_RELEASE:
			state.currentFrame = false;
			state.lastFrame = true;
			break;
		default:
			break;
		}
		(*itr).second = state;
		
	}
	KeyState::KeyState(bool last, bool current)
	{
		lastFrame = last;
		currentFrame = current;
	}
	void mouseCallback(GLFWwindow* w, double x, double y) {
		*AegisSystems::mousePosition = glm::vec2(x, y);
	}



	AegisSystems::AegisSystems(unsigned int width, unsigned int height)
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
		AegisSystems::as = this;
		glfwSetKeyCallback(window, inputCallback);
		glfwSetCursorPosCallback(window, mouseCallback);

		clearColor = new glm::vec3();
		systems = new std::vector<BaseSystem*>;
		mousePosition = new glm::vec2();

		keyStates = new std::map<int, KeyState>;
		
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

		window = glfwCreateWindow(height, width, "Woo Aegis", nullptr, nullptr);

		if (!window) {
			std::cout << "Failed to create window\n";
			Aegis_Exit();
			return -1;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD\n";
			Aegis_Exit();
			return -1;
		}

		glViewport(0, 0, width, height);
		return 0;
	}

	void AegisSystems::Aegis_BeginLoop(void)
	{
		float oldTime;
		float time = 0;
		
		
		float dt;
		glfwMakeContextCurrent(window);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			if (GetKeyTriggered(GLFW_KEY_ESCAPE)) {
				SceneSystem* scenesys = (SceneSystem*)as->Aegis_GetSystem("SceneSystem");
				if (scenesys != nullptr) {
					scenesys->SetNextScene(nullptr);
				}
				else {
					Aegis_Exit();
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
			

			for (auto itr = keyStates->begin(); itr != keyStates->end(); itr++) {
				(*itr).second.lastFrame = false;
				(*itr).second.currentFrame = false;
			}

			glfwSwapBuffers(window);
			
		}
		delete clearColor;
		delete keyStates;
		delete systems;
		delete mousePosition;
		glfwDestroyWindow(window);
		glfwTerminate();
		
	}

	void AegisSystems::Aegis_Exit(void) {
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

	void AegisSystems::Aegis_SetClearColor(glm::vec3 color)
	{
		*clearColor = color;
	}

	void AegisSystems::Aegis_AddSystem(BaseSystem* system)
	{
		systems->push_back(system);
	}

	Aegis::BaseSystem* AegisSystems::Aegis_GetSystem(std::string name)
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
		return AegisSystems::as;
	}
	float AegisSystems::GetTime()
	{
		return (float)glfwGetTime();
	}
	bool AegisSystems::GetKey(int key)
	{
		auto itr = AegisSystems::keyStates->find(key);
		if (itr != AegisSystems::keyStates->end())
			return (*itr).second.currentFrame;
		else
			return false;
	}
	bool AegisSystems::GetKeyTriggered(int key)
	{
		auto itr = AegisSystems::keyStates->find(key);
		if (itr != AegisSystems::keyStates->end())
			return (*itr).second.currentFrame && !(*itr).second.lastFrame;
		else
			return false;
	}
	bool AegisSystems::GetKeyReleased(int key)
	{
		auto itr = AegisSystems::keyStates->find(key);
		if (itr != AegisSystems::keyStates->end())
			return (*itr).second.lastFrame && !(*itr).second.currentFrame;
		else
			return false;
	}
	const glm::vec2* AegisSystems::GetMousePosition()
	{
		return mousePosition;
	}
}


