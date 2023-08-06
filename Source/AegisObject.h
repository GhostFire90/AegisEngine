#pragma once

#include <string>
#include <vector>

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
	class Component;

	/// <summary>
	/// AegisObjects serve as an object handled by an ObjectManager or manually updated by the user
	/// </summary>
	class AEGIS_API AegisObject {
	public:
		/// <summary>
		/// Constructor for an Aegis object, parent can be null
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="parent">Nullable, object it belongs to (nonfunctional as of 7/28/23)</param>
		AegisObject(const char* name, AegisObject* parent = nullptr);
		/// <summary>
		/// Clones an AegisObject, including newly cloned components
		/// </summary>
		/// <param name="other">object to clone</param>
		AegisObject(const AegisObject& other);
		/// <summary>
		/// AegisObject Destructor, frees all components
		/// </summary>
		~AegisObject();

		/// <summary>
		/// calls all component updates
		/// </summary>
		/// <param name="dt">time between last frame and current</param>
		virtual void Update(float dt);
		/// <summary>
		/// calls all component renders
		/// </summary>
		/// <param name="dt">time between last frame and current</param>
		virtual void Render(float dt);

		/// <summary>
		/// Sets the parent object
		/// </summary>
		/// <param name="parent">Nullable, object it belongs to (nonfunctional as of 7/28/23)</param>
		void SetParent(AegisObject* parent);
		/// <summary>
		/// Getter for the parent
		/// </summary>
		/// <returns>Nullable, a const pointer to the parent</returns>
		const AegisObject* GetParent() const;
		/// <summary>
		/// Getter for the name
		/// </summary>
		/// <returns>the objects name</returns>
		const std::string* GetName() const;

		/// <summary>
		/// Adds a component to the list of components, sets the components parent to this
		/// </summary>
		/// <param name="comp">a pointer to the component to add</param>
		void AddComponent(Component* comp);
		/// <summary>
		/// Returns a pointer to a component in the list, can be null
		/// </summary>
		/// <param name="name">the name of the component</param>
		/// <returns>Pointer to valid component, Nullpointer if it doesnt exist</returns>
		Component* GetComponent(const char *name) const;
		/// <summary>
		/// Removes a component from the list, first one it finds
		/// </summary>
		/// <param name="name">Name of the component</param>
		void RemoveComponent(const char* name);

		/// <summary>
		/// whether the object gets cleared from the manager when a new scene loads
		/// </summary>
		/// <param name="dontDestroy">if true, the object wont get destroyed when a new scene is loaded/restarted</param>
		void DontDestroyOnLoad(bool dontDestroy);
		/// <summary>
		/// Tags the object to be destroyed on the next frame 
		/// </summary>
		void Destroy();

		/// <summary>
		/// Whether it is to be destroyed next frame
		/// </summary>
		/// <returns>true if it is queued to be destroyed</returns>
		bool GetDestroyed();
		friend class ObjectManager;
	private:
		std::string* name;
		AegisObject* parent;
		std::vector<Component*>* components;
		bool isDestroyed, destroyOnLoad;
	};
}