#pragma once

#include "Scene.h"

namespace Aegis {
	class AegisObject;
	class Mesh;
	class ShaderSource;
	class Material;
	class Texture;
	class Scene1 : public Scene {
	public:
		void Load() override;
		void Init() override;

		void Update(float dt) override;

		void Exit() override;
		void Unload() override;

	private:
		AegisObject* camera;
		AegisObject* monkey;
		AegisObject* cube;

		Mesh *mCube, *mMonkey;
		ShaderSource *sUV, *sTextured;
		Material *UVmatPrefab, *TexturedmatPrefab;
		
		Texture *beans;
	};
}
