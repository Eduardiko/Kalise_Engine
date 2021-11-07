#include "Globals.h"
#include "Application.h"
#include "UiObjects.h"
#include "GameObject.h"
#include "BaseScene.h"



UiObjects::UiObjects(Application* app, bool start_enabled) : UiWindow(app, start_enabled)
{
	App = app;
}

UiObjects::~UiObjects()
{
}

bool UiObjects::Start()
{
	bool ret = true;

	active = false;

	return ret;
}

update_status UiObjects::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;

}

update_status UiObjects::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (!active) return ret;

	ImGui::Begin("Objects");
	
	

	std::vector<GameObject*> tmpList = App->scene->GetObjectList();

	if (ImGui::TreeNode("Game Objects"))
	{
		for (int i = 0; i < tmpList.size(); i++)
		{
			for (auto component : tmpList[i]->GetComponents())
			{
				if (component->type == ComponentType::TRANSFORM)
				{
					if (i == 0)
						ImGui::SetNextItemOpen(true, ImGuiCond_Once);

					if (ImGui::TreeNode((void*)(intptr_t)i, tmpList[i]->name.c_str(), i))
					{
						float3 position = component->transform->GetPos();
						ImGui::Text(" Position    X: %d", (int)position.x);
						ImGui::SameLine();
						ImGui::Text("Y: %d", (int)position.y);
						ImGui::SameLine();
						ImGui::Text("Z: %d", (int)position.z);

						Quat rotation = component->transform->GetRot();
						ImGui::Text(" Rotation    X: %d", (int)rotation.x);
						ImGui::SameLine();
						ImGui::Text("Y: %d", (int)rotation.y);
						ImGui::SameLine();
						ImGui::Text("Z: %d", (int)rotation.z);

						float3 scale = component->transform->GetScale();
						ImGui::Text(" Scale       X: %d", (int)scale.x);
						ImGui::SameLine();
						ImGui::Text("Y: %d", (int)scale.y);
						ImGui::SameLine();
						ImGui::Text("Z: %d", (int)scale.z);

						ImGui::TreePop();
					}
				}
			}
		}
		ImGui::TreePop();
	}

	ImGui::End();


	return ret;
}

update_status UiObjects::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

bool UiObjects::CleanUp()
{
	bool ret = true;

	return ret;
}
