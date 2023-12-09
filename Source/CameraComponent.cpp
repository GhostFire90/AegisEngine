#include "CameraComponent.h"

#include "AegisObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glfw3.h>
#include "AegisSystems.h"

#include <glm/vec2.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
namespace Aegis {
	CameraComponent::CameraComponent() : Component("CameraComponent"), isViewDirty(true), isProjectionDirty(true)
	{
		position = new glm::vec3(0);
		rotation = new glm::vec3(0);
		viewMatrix = new glm::mat4(1);
		projectionMatrix = new glm::mat4(1);
		fov = glm::radians(45.0f);
		orthographic = false;

	}
	CameraComponent::~CameraComponent()
	{
	}
	CameraComponent::CameraComponent(const CameraComponent& other) : Component(other.name->c_str()), projectionMatrix(new glm::mat4), viewMatrix(new glm::mat4)
	{

		this->rotation = other.rotation;
		this->position = other.position;
		this->isViewDirty = true;

		this->fov = other.fov;
		this->orthographic = other.orthographic;
		this->isProjectionDirty = true;

	}
	void CameraComponent::Update(float dt)
	{
	}
	void CameraComponent::Render(float dt)
	{
	}
	Component* CameraComponent::Clone()
	{
		return new CameraComponent(*this);
	}
	void CameraComponent::SetRotation(glm::vec3 _rotation)
	{
		*rotation = _rotation;
		isViewDirty = true;
	}
	void CameraComponent::SetPosition(glm::vec3 _position)
	{
		*position = _position;
		isViewDirty = true;
	}
	void CameraComponent::SetFOV(float _fov)
	{
		fov = _fov;
		isProjectionDirty = true;
	}
	void CameraComponent::SetOrthogonal(bool ortho)
	{
		orthographic = ortho;
		isProjectionDirty = true;
	}
	const glm::mat4& CameraComponent::GetViewMatrix()
	{
		if (isViewDirty) {

			//glm::quat orientation = glm::toQuat();


			*viewMatrix = glm::mat4(1);
			*viewMatrix = glm::translate(*viewMatrix, -(*position));
			*viewMatrix *= glm::eulerAngleYXZ(-(*rotation).y, -(*rotation).x, -(*rotation).z);//glm::orientate4(-rotation);//glm::eulerAngleXYZ(-rotation.x, -rotation.y, -rotation.z);


			isViewDirty = false;
		}
		return *viewMatrix;
	}
	const glm::mat4& CameraComponent::GetProjectionMatrix()
	{

		if (isProjectionDirty) {
			glm::i32vec2 windim;
			glfwGetWindowSize(AegisSystems::GetAegisSystems()->GetWindow(), &windim.x, &windim.y);

			if (orthographic) {
				*projectionMatrix = glm::ortho(0.0f, (float)windim.x, 0.0f, (float)windim.y);
			}
			else {
				
				*projectionMatrix = glm::perspective(fov, (float)windim.x / (float)windim.y, 0.1f, 100.0f);
				
			}
			isProjectionDirty = false;
		}
		return *projectionMatrix;
	}
}
