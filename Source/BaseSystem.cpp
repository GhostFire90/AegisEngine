#include "BaseSystem.h"

namespace Aegis {
    BaseSystem::BaseSystem(const char* _name) : name(new std::string(_name))
    {
    }
    BaseSystem::~BaseSystem() {
        delete name;
    }

    const std::string& BaseSystem::GetName()
    {
        return *name;
    }
}

