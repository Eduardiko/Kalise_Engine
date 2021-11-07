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

	ImGui::Begin("Objects");
	
	

	std::vector<GameObject*> tmpList = App->scene->GetObjectList();

	if (ImGui::TreeNode("Game Objects"))
	{
		for (int i = 0; i < tmpList.size(); i++)
		{
			/*std::vector<Component*> pan = tmpList[i]->GetComponents();
			
			for (int i = 0; i < pan.size(); i++)
			{
				if (pan[i]->GetType() == ComponentType::TRANSFORM)
				{
					pan[i]->transform->GetPos();
				}
			}*/

			// Use SetNextItemOpen() so set the default state of a node to be open. We could
			// also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
			if (i == 0)
				ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::TreeNode((void*)(intptr_t)i, tmpList[i]->name.c_str(), i))
			{
				ImGui::Text("POS X: ");
				ImGui::SameLine();
				ImGui::Text("POS Y:");
				ImGui::SameLine();
				ImGui::Text("POS Z:");


				ImGui::TreePop();
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
