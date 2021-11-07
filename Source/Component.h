#pragma once

#include "Globals.h"
#include "MathGeoLib.h"
#include "Mesh.h"
#include "Transform.h"

class GameObject;

enum ComponentType
{
	NONE,
	TRANSFORM,
	MESH,
	MATERIAL
};

class Component {
public:
	Component(ComponentType type, bool active = true);
	Component(ComponentType type, Mesh* mesh, bool active = true);

	virtual ~Component();

	virtual void Enable();

	virtual void Update(float dt);

	virtual void Disable();

	Mesh* GetMesh();
	ComponentType GetType() { return type; }

	void AddTransform();

	GameObject* parent;
	ComponentType type;
	Mesh* mesh;
	Transform* transform;

	bool active;
private:


};
