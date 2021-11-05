#pragma once

#include "Globals.h"
#include "MathGeoLib.h"

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
	virtual ~Component();

	virtual void Enable();

	virtual void Update(float dt);

	virtual void Disable();


private:
	bool active;
	GameObject* object;
	ComponentType type;


};

class Transform : public Component {
public:
	Transform();

	float3x4 transformMatrix;
	float3 position;
	float3 scale;
	Quat rotation;
};

//class Mesh : public Component
//{
//public:
//	Mesh(Mesh* mesh);
//
//private:
//	Mesh* mesh = nullptr;
//};