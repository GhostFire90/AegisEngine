#include "Component.h"
#include "AegisObject.h"
#include <algorithm>
namespace Aegis {
	Component::Component(const char* _name) : name(new std::string(_name)), parent(nullptr)
	{
	}
	Component::~Component()
	{
		delete name;
	}
	const std::string* Aegis::Component::GetName() const
	{
		return name;
	}
	const AegisObject* Component::GetParent() const
	{
		return parent;
	}
	void Component::SetParent(AegisObject* _parent)
	{
		parent = _parent;
	}


}

