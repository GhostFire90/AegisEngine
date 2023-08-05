# Aegis Engine

## Foreword
Aegis Engine is a personal project that I decided to undertake that by no means is meant for professional use. I cant speak to its performance or anything of the sort as I have not done any complex testing, this is more of a proof of concept to myself that I understand to some capacity how an OpenGL graphics engine would be built.

## Usage

Aegis is a C++ only library that uses [GLM](https://github.com/g-truc/glm) for its mathematical types so it is recommended to include those in your projects as well.

### Getting a window displayed 
First things first, we should at least get the window running.
```c++
#include <Aegis2/AegisSystems.h>

using namespace Aegis;

int main(void){
  auto as = AegisSystems(800,800); //initialize aegis systems with the width and height of 800
  AegisSystems::Aegis_BeginLoop(); // Everything after this call is out of your hands as by the time the loop ends, aegis will have exited and dealoccated all of its memory


  return 0;  

}

```
### Static objects

Now as the comment shows, after the loop exits the application will close. This doesnt seem too useful as we wont be able to have static or dynamic objects as no render calls are happening, thats where Systems come in. Aegis ships with 2 systems as well as a base class to derive your own, systems are added before the loop starts and update every frame until the loop ends. 

for single scene and static objects we could just add the ObjectManager system

```c++
#include <Aegis2/AegisSystems.h>
#include <Aegis2/ObjectManager.h>

using namespace Aegis;

int main(void){
  auto as = AegisSystems(800,800); //initialize aegis systems with the width and height of 800
  
  auto objManager = new ObjectManager();      //create a manager and track it so we can add objects to it
  AegisSystems::Aegis_AddSystem(objManager);  //Add it to aegis so it will be updated every frame

  /*
  * now we are free here to create and add components to objects as we please and they will be updated and rendered every frame
  */

  AegisSystems::Aegis_BeginLoop(); // Everything after this call is out of your hands as by the time the loop ends, aegis will have exited and dealoccated all of its memory


  return 0;  

}
```

### Dynamic Objects with Scenes

SceneSystem is another system that comes with Aegis, it mannages all scene/level loading and unloading as well as their update functions through the abstract base class of Scene that will need to be implemented then a pointer to the scene will be passed to the SetNextScene function (this should be heap allocated)

```c++
#include <Aegis2/AegisSystems.h>
#include <Aegis2/ObjectManager.h>
#include <Aegis2/SceneSystem.h>
#include "MyScene.h"

using namespace Aegis;

int main(void){
  auto as = AegisSystems(800,800); //initialize aegis systems with the width and height of 800
  
  auto objManager = new ObjectManager();      //create a manager and track it so we can add objects to it
  AegisSystems::Aegis_AddSystem(objManager);  //Add it to aegis so it will be updated every frame

  auto sceneSys = new SceneSystem();          //create the scene system
  AegisSystems::Aegis_AddSystem(sceneSys);    //add it to the engine

  sceneSys.SetNextScene(new MyScene());

  AegisSystems::Aegis_BeginLoop(); // Everything after this call is out of your hands as by the time the loop ends, aegis will have exited and dealoccated all of its memory


  return 0;  

}
```

## Credits

Engine Code:
Rei Anderson

This engine uses:  
[GLM](https://github.com/g-truc/glm) - For mathmatic types  
[GLFW](https://github.com/glfw/glfw) - For window creation and input processing  
[glad](https://github.com/Dav1dde/glad) - For opengl function loading  

