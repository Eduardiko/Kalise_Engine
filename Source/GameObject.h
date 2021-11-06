#pragma once

#include "Component.h"
#include "Mesh.h"
#include "Transform.h"

#include <string>
#include <vector>

class Component;

class GameObject {
public:
	GameObject(std::string name_, bool active = true);
	~GameObject();

	void Update(float dt);
	bool CleanUp();

	Component* CreateComponent(ComponentType type, Mesh* mesh);

	void AddMesh(ComponentType type, Mesh* mesh);

	Transform* GetTransform();

	std::vector<Component*> componentList;
private:

	bool active;
	std::string name;

	GameObject* parent = nullptr;
	std::vector<GameObject*> childrenList;
};