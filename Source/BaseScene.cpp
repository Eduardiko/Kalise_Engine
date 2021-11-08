#include "Globals.h"
#include "Application.h"
#include "BaseScene.h"
#include "GameObject.h"
#include "glew.h"

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
	return true;
}

bool BaseScene::Start()
{
	App->ui->LoadScene("Assets/BakerHouse.fbx", "Baker House");

	glEnable(GL_TEXTURE_2D);

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
				component->GetMesh()->Render();
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
