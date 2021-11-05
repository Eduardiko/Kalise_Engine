#include "Component.h"

Component::Component(ComponentType type, bool active)
{
	type = type;
	active = active;
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

Transform::Transform() : Component(ComponentType::TRANSFORM)
{
	float3 pos(2.0f, 2.0f, 2.0f);
	float3 scale(2.0f, 2.0f, 2.0f);
	Quat rotation(0, 0, 0, 0);

	transformMatrix.Decompose(position, rotation, scale);

}


//Mesh::Mesh(Mesh* mesh) : Component(ComponentType::MESH)
//{
//	this->mesh = mesh;
//}