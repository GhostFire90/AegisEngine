#pragma once

#include "Scene.h"


namespace Aegis {
	class AegisObject;
	class Mesh;
	class ShaderSource;
	class Material;
	class Texture;
	
	class LightingTestScene : public Scene {
	public:
		void Load() override;
		void Init() override;

		void Update(float dt) override;

		void Exit() override;
		void Unload() override;
	private:
		AegisObject *camera, *sphere;
		ShaderSource* sSphere;
		Material* matSphere;
		Mesh* mSphere;
		Texture* beans;
	};
}