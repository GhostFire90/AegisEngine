#pragma once

#include <string>

#ifdef AEGIS_DLL_BUILD
#define AEGIS_API __declspec(dllexport)
#else
#define AEGIS_API __declspec(dllimport)
#endif // !AEGIS_DLL_BUILD

namespace Aegis {
	class AegisObject;
	/// <summary>
	/// Base class for all Components
	/// </summary>
	class AEGIS_API Component {
	public:
		/// <summary>
		/// Constrcuctor for the class
		/// </summary>
		/// <param name="name">Sets the name</param>
		Component(const char* name);
		
		~Component();

		//In all technicallity all rendering can be done in update and vice versa, its more for organization
		virtual void Update(float dt) = 0;
		virtual void Render(float dt) = 0;

		/// <summary>
		/// Getter for the name
		/// </summary>
		/// <returns>Name of the component</returns>
		const std::string* GetName() const;
		/// <summary>
		/// Getter for the parent
		/// </summary>
		/// <returns>returns the parent of the component, should not be called before added to an object</returns>
		const AegisObject* GetParent() const;

		/// <summary>
		/// Sets the parent of the component
		/// </summary>
		/// <param name="parent">pointer to an AegisObject that will act as its parent</param>
		void SetParent(AegisObject* parent);

		/// <summary>
		/// Clone function, basically a wrapper around all the children's copy constructor
		/// </summary>
		/// <returns>newly allocated component cloned of this</returns>
		virtual Component* Clone() = 0;
		
	protected:
		std::string* name;
		AegisObject* parent;
		
	};
}