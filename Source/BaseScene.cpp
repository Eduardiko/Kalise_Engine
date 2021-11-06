#include "Application.h"
#include "BaseScene.h"
#include "GameObject.h"



BaseScene::BaseScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

BaseScene::~BaseScene()
{
	for (int i = 0; i < objectList.size(); i++) {
		delete objectList[i];
	}
}

bool BaseScene::Init()
{
	return false;
}

bool BaseScene::Start()
{

	for (int i = 0; i < objectList.size(); i++) {
		for (auto component : objectList[i]->GetComponents())
		{
			if (component->GetType() == ComponentType::MESH)
				component->GetMesh()->InitBuffers();
		}
	}

	return false;
}

update_status BaseScene::PreUpdate(float dt)
{
	return update_status();
}

update_status BaseScene::Update(float dt)
{
	for (int i = 0; i < objectList.size(); i++) {
		for (auto component : objectList[i]->GetComponents())
		{
			if (component->GetType() == ComponentType::MESH)
				component->GetMesh()->Render();
		}
	}
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
