#pragma once

#include "Globals.h"
#include "Module.h"
#include <vector>

class GameObject;

class BaseScene : public Module{
public:
	BaseScene(Application* app, bool start_enabled = true);
	~BaseScene();

	bool Init();
	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	bool CleanUp();

	std::vector<GameObject*> objects;

private:
	GameObject* parent = nullptr;

	std::vector<GameObject> objectList;
};