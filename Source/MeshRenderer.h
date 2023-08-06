#pragma once

#include "Component.h"

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
	class Mesh;
	class Material;

	/// <summary>
	/// MeshRenderer is for rendering a mesh (wow surprising)
	/// </summary>
	class AEGIS_API MeshRenderer : public Component {
	public:

		/// <summary>
		/// Creates a MeshRenderer component
		/// </summary>
		/// <param name="mesh">Pointer to loaded mesh</param>
		/// <param name="mat">A reference to a material, whether it is "Real" or not it treats it as a prefab</param>
		MeshRenderer(Mesh* mesh, const Material& mat);
		 
		//MeshRenderer(const char* mesh_path, const char* vertex_path, const char* frag_path, AegisObject& parent);

		/// <summary>
		/// MeshRenderer Destructor, frees the "Real" material that was created
		/// </summary>
		~MeshRenderer();
		
		//unused
		void Update(float dt) override;

		/// <summary>
		/// Renders the mesh using the material 
		/// </summary>
		/// <param name="dt">time between last frame and current, unused</param>
		void Render(float dt) override;

		/// <summary>
		/// Clones the component
		/// </summary>
		/// <returns>A clone of the component</returns>
		Component* Clone() override;

		/// <summary>
		/// Returns the pointer to the material instance used by the renderer
		/// </summary>
		/// <returns>Pointer to Material instance</returns>
		Material* GetMaterial();

	private:
		MeshRenderer(const MeshRenderer& other);

		Mesh* mesh;
		Material* material;
	};
}