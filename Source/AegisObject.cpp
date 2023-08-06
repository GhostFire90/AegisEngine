#include "AegisObject.h"
#include "Component.h"
#include <algorithm>

namespace Aegis {
	AegisObject::AegisObject(const char* _name, AegisObject* _parent) : parent(_parent), isDestroyed(false), destroyOnLoad(true)
	{
		name = new std::string(_name);
		components = new std::vector<Component*>;
	}
	AegisObject::AegisObject(const AegisObject& other)
	{
		name = new std::string(*other.name);
		parent = nullptr;
		isDestroyed = false;
		destroyOnLoad = true;
		components = new std::vector<Component*>;

		for (auto itr = other.components->begin(); itr != other.components->end(); itr++) {
			components->push_back((*itr)->Clone());
		}
	}
	AegisObject::~AegisObject()
	{
		for (auto itr = components->begin(); itr != components->end(); itr++) {
			delete (*itr);
		}
		delete components;
		delete name;
	}
	void AegisObject::Update(float dt)
	{
		for (auto itr = components->begin(); itr != components->end(); itr++) {
			(*itr)->Update(dt);
		}
	}
	void AegisObject::Render(float dt)
	{
		for (auto itr = components->begin(); itr != components->end(); itr++) {
			(*itr)->Render(dt);
		}
	}
	void AegisObject::SetParent(AegisObject* _parent)
	{
		parent = _parent;
	}
	const AegisObject* AegisObject::GetParent() const
	{
		return parent;
	}
	const std::string* AegisObject::GetName() const
	{
		return name;
	}
	void AegisObject::AddComponent(Component* comp)
	{
		comp->SetParent(this);
		components->push_back(comp);
	}
	Component* AegisObject::GetComponent(const char* _name) const
	{
		std::string name(_name);
		auto c = std::find_if(components->begin(), components->end(), [name](Component* comp) -> bool {
			return name.compare(*comp->GetName()) == 0;
			});
		if (c == components->end()) {
			return nullptr;
		}
		return *c;
	}
	void AegisObject::RemoveComponent(const char* _name)
	{
		std::string name(_name);
		auto c = std::find_if(components->begin(), components->end(), [name](Component* comp) -> bool {
			return name.compare(*comp->GetName()) == 0;
			});
		if (c != components->end()) {
			delete (*c);
			components->erase(c);
		}
		
	}
	void AegisObject::DontDestroyOnLoad(bool destroyonload)
	{
		destroyOnLoad = !destroyonload;
	}
	void AegisObject::Destroy()
	{
		isDestroyed = true;
	}
	bool AegisObject::GetDestroyed()
	{
		return isDestroyed;
	}
}

