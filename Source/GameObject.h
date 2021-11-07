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

	void CreateComponent(ComponentType type, Mesh* mesh);

	void AddMesh(ComponentType type, Mesh* mesh);

	std::vector<Component*> GetComponents();

	std::vector<Component*> componentList;
	GameObject* parent = nullptr;
	std::string name;
private:

	bool active;

	std::vector<GameObject*> childrenList;
};