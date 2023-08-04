#include "Scene.h"

namespace Aegis {
	Scene::Scene()
	{
		ambientLightColor = new glm::vec4();
	}
	Scene::~Scene() {
		delete ambientLightColor;
		return;
	}
}