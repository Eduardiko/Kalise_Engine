#pragma once

#include <vector>

class GameObject;

class BaseScene {
public:
	BaseScene();
	~BaseScene();

	std::vector<GameObject*> objects;
};