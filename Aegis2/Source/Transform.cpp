#include "Transform.h"
#include "AegisObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Aegis {
	Transform::Transform() : Component("Transform"),
		isDirty(false), position(new glm::vec3(0)), rotation(new glm::vec3(0)), scale(new glm::vec3(1)), transformMatrix(new glm::mat4(1))
	{
	}
	Transform::~Transform()
	{
		delete position;
		delete rotation;
		delete scale;
		delete transformMatrix;
	}
	void Transform::Update(float dt)
	{
	}
	void Transform::Render(float dt)
	{
	}
	Component* Transform::Clone()
	{
		return new Transform(*this);
	}
	glm::mat4 Transform::GetMatrix()
	{
		
		if (isDirty) {

			glm::quat orientation = glm::toQuat(glm::orientate3(*rotation));
			*transformMatrix = glm::mat4(1);

			*transformMatrix = glm::translate(*transformMatrix, *position);
			*transformMatrix *= glm::eulerAngleYXZ(rotation->y, rotation->x, rotation->z);//glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
			*transformMatrix = glm::scale(*transformMatrix, *scale);

			isDirty = false;
		}
		glm::mat4 ret = *transformMatrix;
		if (parent->GetParent() != nullptr) {
			Transform* ptrans = (Transform*)parent->GetParent()->GetComponent("Transform");
			if (ptrans != nullptr) {
				ret = ptrans->GetMatrix() * *transformMatrix;
			}
		}
		return ret;
	}
	const glm::vec3& Transform::GetPosition() const
	{
		return *position;
	}
	const glm::vec3& Transform::GetRotation() const
	{
		return *rotation;
	}
	const glm::vec3& Transform::GetScale() const
	{
		return *scale;
	}
	void Transform::SetPosition(const glm::vec3& pos)
	{
		*position = pos;
		
		isDirty = true;
	}
	void Transform::SetRotation(const glm::vec3& rot)
	{
		*rotation = rot;
		isDirty = true;
	}
	void Transform::SetScale(const glm::vec3& _scale)
	{
		*scale = _scale;
		isDirty = true;
	}
	Transform::Transform(const Transform& other) : Component(other.name->c_str()), transformMatrix()
	{
		position = new glm::vec3(*other.position);
		scale = new glm::vec3(*other.scale);
		rotation = new glm::vec3(*other.rotation);
		isDirty = true;
	}
}