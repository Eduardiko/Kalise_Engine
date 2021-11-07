#pragma once

#include "MathGeoLib.h"

class Gameobject;

class Transform
{
public:
	Transform(bool active = true);
	Transform(float3 position_, Quat rotation_, float3 scale_, bool active = true);
	~Transform();

	void UpdateTransform();

	void SetPosition(float x, float y, float z);
	float3 GetPos();

	void SetRot(Quat q);
	Quat GetRot();

	void SetScale(float x, float y, float z);
	float3 GetScale();


private:

	float4x4 transformMatrix;
	float4x4 lTransform;
	float3 position;
	Quat rotation;
	float3 scale;
};
