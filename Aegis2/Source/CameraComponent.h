#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Component.h"

#ifdef AEGIS_DLL_BUILD
#define AEGIS_API __declspec(dllexport)
#else
#define AEGIS_API __declspec(dllimport)
#endif // !AEGIS_DLL_BUILD

namespace Aegis {

	class AegisObject;
	/// <summary>
	/// A camera component has a dual purpose, it works similarly to Transform with all the rotations and positions flipped
	/// it does this because moving a camera is essentially moving the entire scene
	/// </summary>
	class AEGIS_API CameraComponent : public Component {
	public:
		CameraComponent();
		~CameraComponent();
		
		//these two are unused in this Component;
		void Update(float dt) override;
		void Render(float dt) override;

		/// <summary>
		/// Basically calls the copy constructor of this component and returns a pointer to the new memory
		/// </summary>
		/// <returns>A pointer to the newly allocated component</returns>
		Component* Clone() override;

		/// <summary>
		/// rotation on various axes in radians
		/// </summary>
		/// <param name="rotation">euler angles in radians</param>
		void SetRotation(glm::vec3 rotation);

		/// <summary>
		/// Sets position of the transform
		/// </summary>
		/// <param name="position">the position of the camera</param>
		void SetPosition(glm::vec3 position);

		/// <summary>
		/// FOV of the camera, only used if a perspective camera
		/// </summary>
		/// <param name="fov">FOV in radians</param>
		void SetFOV(float fov);

		/// <summary>
		/// Tells the camera whether its orthogonal or perspective
		/// </summary>
		/// <param name="ortho">True sets it to orthographic mode</param>
		void SetOrthogonal(bool ortho);

		/// <summary>
		/// Returns a reference to the view matrix
		/// it isnt const because its not updating every frame to save computation, it updates the matrix on call if a change has been made
		/// </summary>
		/// <returns>A constant reference to the view matrix</returns>
		const glm::mat4& GetViewMatrix();
		/// <summary>
		/// Returns a reference to the projection matrix
		/// it isnt const because its not updating every frame to save computation, it updates the matrix on call if a change has been made
		/// </summary>
		/// <returns>A constant reference to the projection matrix</returns>
		const glm::mat4& GetProjectionMatrix();

	private:
		CameraComponent(const CameraComponent& other);
		glm::mat4 *viewMatrix;
		glm::vec3 *rotation, *position;
		bool isViewDirty;

		glm::mat4 *projectionMatrix;
		float fov;
		bool orthographic;
		bool isProjectionDirty;
	};
}