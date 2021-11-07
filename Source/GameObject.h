#pragma once

#include "Component.h"


#include <string>
#include <vector>

class Component;


class GameObject {
public:
	GameObject(std::string name_, bool active = true);
	~GameObject();

	void Update(float dt);
	bool CleanUp();

	void CreateComponent(ComponentType type, Mesh* mesh = nullptr, Texture* texture = nullptr);

	Component* AddMesh(ComponentType type, Mesh* mesh, Component* component);
	Component* AddTexture(ComponentType type, Texture* texture, Component* component);

	std::vector<Component*> GetComponents();

	std::vector<Component*> componentList;
	GameObject* parent = nullptr;
	std::string name;
private:

	bool active;

	std::vector<GameObject*> childrenList;
};