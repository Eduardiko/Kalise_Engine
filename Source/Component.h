#pragma once

#include "Globals.h"
#include "MathGeoLib.h"
#include "Mesh.h"

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


	GameObject* parent;
	ComponentType type;
	Mesh* mesh;

	bool active;
private:


};
