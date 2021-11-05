#include "GameObject.h"

#include "Application.h"



GameObject::GameObject(std::string name, bool active)
{
	this->name = name;

}

GameObject::~GameObject()
{
	for (int i = 0; i < componentList.size(); i++) {
		delete componentList[i];
	}
}

void GameObject::Update(float dt)
{
	for (int i = 0; i < componentList.size(); i++) {
		componentList[i]->Update(dt);
	}

	for (int i = 0; i < childrenList.size(); i++) {
		childrenList[i]->Update(dt);
	}
}

Component* GameObject::CreateComponent(ComponentType type)
{
	Component* component = new Component(type);

	return component;
}