#include "LightingTestScene.h"
#include "Shader.h"
#include "ShaderSource.h"
#include "Mesh.h"
#include "AegisObject.h"
#include "Material.h"
#include "ObjectManager.h"
#include "AegisSystems.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "CameraComponent.h"
#include "Image.h"


namespace Aegis {
	void LightingTestScene::Load()
	{
		sSphere = new ShaderSource("Shaders/UnlitPersp.vert", "Shaders/LitPersp.frag");
		mSphere = new Mesh("Meshs/backpack.obj");
		matSphere = new Material("Sphere", *sSphere);
		beans = new Texture("Textures/diffuse.jpg");
		matSphere->SetTexture(beans, 0);

	}
	void LightingTestScene::Init()
	{
		ObjectManager* manager = (ObjectManager*)AegisSystems::GetAegisSystems()->Aegis_GetSystem("ObjectManager");

		camera = new AegisObject("Camera", nullptr);
		CameraComponent* camComp = new CameraComponent();
		camComp->SetPosition(glm::vec3(0, .5f, 4));
		camComp->SetRotation(glm::vec3(glm::radians(-25.0f), 0, 0));
		camComp->SetFOV(glm::radians(45.0f));
		camera->AddComponent(camComp);

		sphere = new AegisObject("Sphere", nullptr);
		Transform* trans = new Transform();
		trans->SetPosition(glm::vec3(0, 0, 0));
		trans->SetRotation(glm::vec3(glm::radians(-45.0f), glm::radians(25.0f), glm::radians(.0f)));
		trans->SetScale(glm::vec3(.5));
		
		sphere->AddComponent(trans);
		sphere->AddComponent(new MeshRenderer(mSphere, *matSphere));

		manager->SetActiveCamera(camComp);
		manager->AddObject(camera);
		manager->AddObject(sphere);
		ambientLightColor = glm::vec4(.1f, .1f, .1f, 1.0f);
	}
	void LightingTestScene::Update(float dt)
	{
		Material* real = ((MeshRenderer*)sphere->GetComponent("MeshRenderer"))->GetMaterial();
		Shader* shader = real->GetShader();
		CameraComponent* camComp = (CameraComponent*)camera->GetComponent("CameraComponent");

		float time = AegisSystems::GetTime();


		shader->SetVec3("lights[0].Pos", glm::vec3(camComp->GetViewMatrix()*glm::vec4(1, 2, 1, 1)));
		shader->SetVec4("lights[0].Color", glm::vec4(1, 1, 1, 1));
		shader->SetInt("lightCount", 1);
		shader->SetVec4("ambientLight", ambientLightColor);
	}
	void LightingTestScene::Exit()
	{
	}
	void LightingTestScene::Unload()
	{
		delete sSphere;
		delete mSphere;
		delete matSphere;
		delete beans;
	}
}