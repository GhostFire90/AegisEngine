#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

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

namespace Aegis {
	class AegisObject;

	/// <summary>
	/// A transform component, stores position, rotation and scale
	/// </summary>
	class AEGIS_API Transform : public Component {
	public:

		/// <summary>
		/// Default constructor of the component
		/// </summary>
		Transform();
		
		~Transform();


		//Unused
		void Update(float dt) override;
		void Render(float dt) override;

		/// <summary>
		/// Clones the component
		/// </summary>
		/// <returns>a copy of the component</returns>
		Component* Clone() override;

		/// <summary>
		/// Returns the calculated matrix, calculated only when this is called and it has been modified
		/// </summary>
		/// <returns>The calculated matrix given the position rotation and scale</returns>
		glm::mat4 GetMatrix();
		/// <summary>
		/// Getter for the position
		/// </summary>
		/// <returns>reference to the position vector</returns>
		const glm::vec3& GetPosition() const;
		/// <summary>
		/// getter for euler angles rotations
		/// </summary>
		/// <returns>reference to the Euler Angle vector</returns>
		const glm::vec3& GetRotation() const;
		/// <summary>
		/// getter for the scale
		/// </summary>
		/// <returns>reference to the Scale vector</returns>
		const glm::vec3& GetScale() const;

		/// <summary>
		/// Setter for the positon
		/// </summary>
		/// <param name="pos">position to set to the transform</param>
		void SetPosition(const glm::vec3& pos);
		/// <summary>
		/// Setter for the rotatation
		/// </summary>
		/// <param name="rot">Euler Angles in radians to set to the transform</param>
		void SetRotation(const glm::vec3& rot);
		/// <summary>
		/// Setter for scale
		/// </summary>
		/// <param name="scale">scale vector to set to the transform</param>
		void SetScale(const glm::vec3& scale);

	private:

		Transform(const Transform& other);

		glm::mat4 *transformMatrix;
		glm::vec3 *position, *rotation, *scale;
		
		bool isDirty;
	};
}
