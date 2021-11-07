#pragma once

#include "Module.h"
#include <vector>

class Application;
class GameObject;

class BaseScene : public Module {
public:
	BaseScene(Application* app, bool start_enabled = true);
	~BaseScene();

	bool Init();
	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	std::vector<GameObject*> GetObjectList();

	bool CleanUp();

	std::vector<GameObject*> objectList;

	GameObject* parent = nullptr;
private:

};