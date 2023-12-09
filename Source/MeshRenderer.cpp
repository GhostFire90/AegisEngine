#include "MeshRenderer.h"
#include "Component.h"
#include "AegisObject.h"
#include "CameraComponent.h"
#include "ObjectManager.h"
#include "SceneSystem.h"
#include "Transform.h"
#include "Shader.h"
#include "Material.h"
#include "Mesh.h"

#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

namespace Aegis {

	MeshRenderer::MeshRenderer(Mesh* _mesh, const Material& mat) : Component("MeshRenderer")
	{
		mesh = _mesh;
		material = new Material(mat);
	}
	MeshRenderer::~MeshRenderer()
	{
		delete mesh;
		delete material;
	}
	void MeshRenderer::Update(float dt)
	{
	}
	void MeshRenderer::Render(float dt)
	{
		CameraComponent* cam = SceneSystem::GetSceneSystem()->GetActiveCamera();

		const glm::mat4& view = cam->GetViewMatrix();
		const glm::mat4& proj = cam->GetProjectionMatrix();
		glm::mat4 transform = glm::mat4(1);

		Transform* trans = (Transform*)parent->GetComponent("Transform");
		if (trans != nullptr) {
			transform = trans->GetMatrix();
		}

		/*std::cout << "View: " << glm::to_string(view) << '\n';
		std::cout << "Proj: " << glm::to_string(proj) << '\n';
		std::cout << "Trans: " << glm::to_string(transform) << '\n';*/
		material->Use();
		Shader* shader = material->GetShader();
		shader->SetMat4("view", view);
		shader->SetMat4("projection", proj);
		shader->SetMat4("transform", transform);
		shader->SetMat4("normalMatrix", glm::transpose(glm::inverse(view*transform)));
		
		mesh->Render();
	}
	Component* MeshRenderer::Clone()
	{
		return new MeshRenderer(*this);
	}
	Material* MeshRenderer::GetMaterial()
	{
		return material;
	}

	MeshRenderer::MeshRenderer(const MeshRenderer& other) : Component(other.name->c_str()) 
	{
		mesh = other.mesh;
		material = new Material(*other.material);
	}

}