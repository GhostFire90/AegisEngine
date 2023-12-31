target_sources(Aegis2
    PRIVATE
    Source/AegisObject.cpp
    Source/AegisSystems.cpp
    Source/BaseSystem.cpp
    Source/CameraComponent.cpp
    Source/Component.cpp
    Source/Material.cpp
    Source/Mesh.cpp
    Source/MeshRenderer.cpp
    Source/obj_loader.cpp
    Source/ObjectManager.cpp
    Source/Scene.cpp
    Source/SceneSystem.cpp
    Source/Shader.cpp
    Source/ShaderSource.cpp
    Source/Texture.cpp
    Source/Transform.cpp
    Source/AegisObject.h
    Source/AegisSystems.h
    Source/BaseSystem.h
    Source/CameraComponent.h
    Source/Component.h
    Source/Material.h
    Source/Mesh.h
    Source/MeshRenderer.h
    Source/obj_loader.h
    Source/ObjectManager.h
    Source/Scene.h
    Source/SceneSystem.h
    Source/Shader.h
    Source/ShaderSource.h
    Source/Texture.h
    Source/Transform.h
    Source/glad.c
)
target_include_directories(Aegis2 PUBLIC inc)


message("${CMAKE_SOURCE_DIR}/lib")

if(WIN32)
target_link_directories(Aegis2 PUBLIC lib)
target_link_libraries(Aegis2 PUBLIC opengl32 glfw3)
endif()
if(UNIX)
target_link_libraries(Aegis2 PUBLIC GL glfw)
endif()