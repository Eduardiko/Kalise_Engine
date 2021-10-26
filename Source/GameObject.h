#pragma once

#include <string>
#include "Application.h"
#include "MathGeoLib.h"

class Transform;

class GameObject {
public:
	GameObject(Application* app, std::string name);
	~GameObject();

	Transform* transform;

	std::string name;
};

class Transform {
public:
	Transform(Application* app, GameObject* gameObject);

	float3 position;
	float3 rotation;
	float3 scale;
};