
#include <glfw3.h>
#include "AegisSystems.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include "SceneSystem.h"

#include "ObjectManager.h"

using namespace Aegis;


int main(void) {

	AegisSystems as(800, 800);


	ObjectManager* man = new ObjectManager("ObjectManager");
	as.Aegis_AddSystem(man);
	as.Aegis_SetClearColor({ 0.2f, 0.3f, 0.3f });
	

	SceneSystem* scenesys = new SceneSystem();
	Scene1* s1 = new Scene1();
	scenesys->SetNextScene(s1);
	as.Aegis_AddSystem(scenesys);
	
	
	as.Aegis_BeginLoop();

	
	
	//Aegis::Aegis_Exit();	

	return 0;

}