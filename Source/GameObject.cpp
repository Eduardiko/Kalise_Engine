#include "GameObject.h"

#include "Application.h"

Transform::Transform(Application* app, GameObject* gameObject) {
	

	//this->position.Set(0.0f, 0.0f, 0.0f);
	this->position.x = 0.0f;
	this->position.y = 0.0f;
	this->position.z = 0.0f;

	//this->rotation.Set(0.0f, 0.0f, 0.0f);
	this->rotation.x = 0.0f;
	this->rotation.y = 0.0f;
	this->rotation.z = 0.0f;

	//this->scale.Set(0, 0, 0);
	this->scale.x = 0.0f;
	this->scale.y = 0.0f;
	this->scale.z = 0.0f;
}

GameObject::GameObject(Application* app, std::string name) {
	this->name = name;
	this->transform = new Transform(app, this);
}

GameObject::~GameObject()
{
	delete transform;
}