#include "Transform.h"

Transform::Transform(bool active) : Component(type, active)
{
	type = ComponentType::TRANSFORM;

	position.x = 0;
	position.y = 0;
	position.z = 0;

	rotation = Quat::identity;

	scale.x = 0;
	scale.y = 0;
	scale.z = 0;

	lTransform = float4x4::FromTRS(position, rotation, scale);
	transformMatrix = lTransform;
}

Transform::Transform(float3 position_, Quat rotation_, float3 scale_, bool active) : Component(type, active)
{
	type = ComponentType::TRANSFORM;

	position.x = position_.x;
	position.y = position_.y;
	position.z = position_.z;

	rotation.x = rotation_.x;
	rotation.y = rotation_.y;
	rotation.z = rotation_.z;
	
	scale.x = scale_.x;
	scale.y = scale_.y;
	scale.z = scale_.z;

	lTransform = float4x4::FromTRS(position, rotation, scale);
	transformMatrix = lTransform;
}

Transform::~Transform()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	rotation = Quat::identity;

	scale.x = 0;
	scale.y = 0;
	scale.z = 0;

	lTransform.zero;
	transformMatrix.zero;
}

void Transform::UpdateTransform()
{
	lTransform = float4x4::FromTRS(position, rotation, scale);
	transformMatrix = lTransform;
}

void Transform::SetPosition(float x, float y, float z)
{
	position.Set(x, y, z);
	UpdateTransform();
}

float3 Transform::GetPos()
{
	return position;
}

void Transform::SetRot(Quat quater)
{
	rotation = quater;
	UpdateTransform();
}

Quat Transform::GetRot()
{
	return rotation;
}

void Transform::SetScale(float x, float y, float z)
{
	scale.Set(x, y, z);
	UpdateTransform();
}

float3 Transform::GetScale()
{
	return scale;
}