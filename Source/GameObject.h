#pragma once

#include "Component.h"
#include "Mesh.h"

#include <string>
#include <vector>
#include "Application.h"

//class Component;

class GameObject {
public:
	GameObject(std::string name, bool active = true);
	~GameObject();

	void Update(float dt);
	Component* CreateComponent(ComponentType type);

private:

	bool active;
	std::string name;
	std::vector<Component*> componentList;

	GameObject* parent = nullptr;
	std::vector<GameObject*> childrenList;
};