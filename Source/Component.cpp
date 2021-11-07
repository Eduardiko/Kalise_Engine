#include "Component.h"

Component::Component(ComponentType type_, bool active_)
{
	type = type_;
	active = active_;
}

Component::Component(ComponentType type_, Mesh* mesh_, bool active_)
{
	type = type_;
	mesh = mesh_;
	active = active_;
}

Component::~Component()
{
}

void Component::Enable()
{
}

void Component::Update(float dt)
{
}

void Component::Disable()
{
}

Mesh* Component::GetMesh() 
{ 
	return mesh; 
}

void Component::AddTransform()
{
	Transform* transform_ = new Transform();

	transform = transform_;

}