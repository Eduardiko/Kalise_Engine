#include "GameObject.h"

#include "Application.h"


GameObject::GameObject(std::string name_, bool active)
{
	name = name_;
	CreateComponent(ComponentType::TRANSFORM);

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

bool GameObject::CleanUp()
{
	return false;
}

void GameObject::CreateComponent(ComponentType type, Mesh* mesh, Texture* texture)
{
	Component* component = nullptr;

	switch (type)
	{
	case TRANSFORM:
	{
		component = new Component(type);
		component->AddTransform();

		break;
	}
	case MESH:
	{
		component = AddMesh(type, mesh, component);
		break;
	}
	case TEXTURE:
	{
		component = AddTexture(type, texture, component);
		break;
	}
	default:
		break;
	}

	if (component != nullptr)
	{
		component->parent = this;
		componentList.push_back(component);
	}
	

}

Component* GameObject::AddMesh(ComponentType type, Mesh* mesh, Component* component)
{
	component = new Component(type, mesh, nullptr);
	return component;
}

Component* GameObject::AddTexture(ComponentType type, Texture* texture, Component* component)
{
	component = new Component(type, nullptr, texture);
	return component;

}

std::vector<Component*> GameObject::GetComponents() {
	return componentList;
}
