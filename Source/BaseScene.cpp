#include "BaseScene.h"
#include "GameObject.h"



BaseScene::BaseScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

BaseScene::~BaseScene()
{
	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
}

bool BaseScene::Init()
{
	return false;
}

bool BaseScene::Start()
{
	return false;
}

update_status BaseScene::PreUpdate(float dt)
{
	return update_status();
}

update_status BaseScene::Update(float dt)
{
	return update_status();
}

update_status BaseScene::PostUpdate(float dt)
{
	return update_status();
}

bool BaseScene::CleanUp()
{
	return false;
}
