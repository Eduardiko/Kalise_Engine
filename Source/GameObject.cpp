#include "GameObject.h"

#include "Application.h"



GameObject::GameObject(std::string name_, bool active)
{
	name = name_;
	CreateComponent(ComponentType::TRANSFORM, nullptr);

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

void GameObject::CreateComponent(ComponentType type, Mesh* mesh)
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
		AddMesh(type, mesh);
		break;
	}
	case MATERIAL:
	{
		/*c = new Material();
		Material* m = (Material*)c;
		m->SetTexture(nullptr);*/
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

void GameObject::AddMesh(ComponentType type, Mesh* mesh)
{
	Component* component = new Component(type, mesh);
	componentList.push_back(component);
}

std::vector<Component*> GameObject::GetComponents() {
	return componentList;
}
