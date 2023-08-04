#include "Scene1.h"
#include "AegisObject.h"
#include "Transform.h"
#include "CameraComponent.h"
#include "MeshRenderer.h"
#include "ObjectManager.h"
#include "AegisSystems.h"
#include <glm/glm.hpp>
#include "Material.h"
#include "ShaderSource.h"
#include "Shader.h"
#include "Mesh.h"
#include "Image.h"
#include "LightingTestScene.h"
#include "SceneSystem.h"
namespace Aegis {
	void Scene1::Load()
	{
		mCube = new Mesh("Meshs/cube.obj");
		mMonkey = new Mesh("Meshs/monkey.obj");

		sUV = new ShaderSource("Shaders/UnlitPersp.vert", "Shaders/FirstTri.frag");
		sTextured = new ShaderSource("Shaders/UnlitPersp.vert", "Shaders/UnlitPersp.frag");
		UVmatPrefab = new Material("UnlitUV", *sUV);
		TexturedmatPrefab = new Material("UnlitTextured", *sTextured);

		beans = new Texture("Textures/beans.png");

		TexturedmatPrefab->SetTexture(beans, 0);

	}
	void Scene1::Init()
	{
		

		cube = new AegisObject("Cube", nullptr);
		monkey = new AegisObject("Monkey", cube);
		camera = new AegisObject("Camera", nullptr);
		ObjectManager* manager = (ObjectManager*)AegisSystems::GetAegisSystems()->Aegis_GetSystem("ObjectManager");
		Transform* t = new Transform();
		t->SetPosition(glm::vec3(1, 0, 0));
		//t->SetRotation(glm::vec3(0, glm::radians(-55.0f), 0));
		monkey->AddComponent(t);
		monkey->AddComponent(new MeshRenderer(mMonkey, *UVmatPrefab));

		t = new Transform();
		//t->SetPosition(glm::vec3(-1, 0, 0));
		cube->AddComponent(t);
		cube->AddComponent(new MeshRenderer(mCube, *TexturedmatPrefab));

		CameraComponent* camComp = new CameraComponent();
		camComp->SetPosition(glm::vec3(0, .5f, 4));
		camComp->SetRotation(glm::vec3(glm::radians(-25.0f), 0, 0));
		camComp->SetFOV(glm::radians(45.0f));
		camera->AddComponent(camComp);

		manager->SetActiveCamera(camComp);
		manager->AddObject(monkey);
		manager->AddObject(cube);
		manager->AddObject(camera);
			
	}
	float ti;
	void Scene1::Update(float dt)
	{
		Transform* t = (Transform*)monkey->GetComponent("Transform");
		t->SetRotation(glm::vec3(0, -ti, 0));
		//t->SetScale(glm::vec3(.5f));

		SceneSystem* scenesys = (SceneSystem*)AegisSystems::GetAegisSystems()->Aegis_GetSystem("SceneSystem");

		glm::vec3 pos = t->GetPosition();
		t->SetPosition(glm::vec3(pos.x, glm::sin(2*ti+.5)*.25, pos.z));

		t = (Transform*)cube->GetComponent("Transform");
		t->SetRotation(glm::vec3(0, -ti, 0));
		ti += 1 * dt;

		if (AegisSystems::GetKeyTriggered('1')) {
			LightingTestScene* ls = new LightingTestScene();
			scenesys->SetNextScene(ls);
		}
	}
	void Scene1::Exit()
	{
	}
	void Scene1::Unload()
	{
		delete sUV;
		delete sTextured;
		delete mCube;
		delete mMonkey;
		delete UVmatPrefab;
		delete TexturedmatPrefab;
		delete beans;
	}
}