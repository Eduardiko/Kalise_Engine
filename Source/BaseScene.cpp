#include "Globals.h"
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
	tempTexture = nullptr;

	return true;
}

bool BaseScene::Start()
{
	App->importer->ImportScene("Assets/BakerHouse.fbx", "Baker House");

	for (int i = 0; i < App->scene->objectList.size(); i++) {
		for (auto component : App->scene->objectList[i]->GetComponents())
		{
			if (component->GetType() == ComponentType::TEXTURE)
				tempTexture = component->GetTexture();
			
		}

		for (auto component : App->scene->objectList[i]->GetComponents())
		{
			if (component->GetType() == ComponentType::MESH)
				component->GetMesh()->InitBuffers(tempTexture);
		}

	}

	return true;
}

update_status BaseScene::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status BaseScene::Update(float dt)
{
	for (int i = 0; i < objectList.size(); i++) {

		for (auto component : objectList[i]->GetComponents())
		{
			if (component->GetType() == ComponentType::MESH)
				component->GetMesh()->Render(tempTexture);
		}
	}

	return UPDATE_CONTINUE;
}

update_status BaseScene::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

std::vector<GameObject*> BaseScene::GetObjectList()
{
	return objectList;
}

bool BaseScene::CleanUp()
{
	return true;
}
