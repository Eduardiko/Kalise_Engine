#include "Globals.h"
#include "Application.h"
#include "UiObjects.h"
#include "BaseScene.h"
#include "GameObject.h"


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
		ImGui::Separator();

		for (int i = 0; i < tmpList.size(); i++)
		{
			if (ImGui::TreeNode((void*)(intptr_t)i, tmpList[i]->name.c_str(), i))
			{
				std::vector<Component*> compList = tmpList[i]->GetComponents();
				for (int j = 0; j < compList.size(); j++)
				{
					if (compList[j]->type == ComponentType::TRANSFORM)
					{
						if (i == 0)
							ImGui::SetNextItemOpen(true, ImGuiCond_Once);

						float3 position = compList[j]->transform->GetPos();
						ImGui::Text("Position");
						ImGui::Text("	X: %d", (int)position.x);
						ImGui::SameLine();
						ImGui::Text("Y: %d", (int)position.y);
						ImGui::SameLine();
						ImGui::Text("Z: %d", (int)position.z);

						Quat rotation = compList[j]->transform->GetRot();
						ImGui::Text("Rotation");
						ImGui::Text("	X: %d", (int)rotation.x);
						ImGui::SameLine();
						ImGui::Text("Y: %d", (int)rotation.y);
						ImGui::SameLine();
						ImGui::Text("Z: %d", (int)rotation.z);

						float3 scale = compList[j]->transform->GetScale();
						ImGui::Text("Scale");
						ImGui::Text("	X: %d", (int)scale.x);
						ImGui::SameLine();
						ImGui::Text("Y: %d", (int)scale.y);
						ImGui::SameLine();
						ImGui::Text("Z: %d", (int)scale.z);
					}

					if (compList[j]->type == ComponentType::MESH)
					{
						auxiliarTexture = compList[j]->mesh->GetTexture();
						if (j == 1)
						{
							if (ImGui::Checkbox("Set CheckerBox Texture", &compList[j]->mesh->checkerTexture))
							{
								if (compList[j]->mesh->checkerTexture)
								{
									compList[j]->mesh->SetCheckerBoxTexture();
									if(compList[j + 1] != nullptr && compList[j + 1]->type == ComponentType::MESH) compList[j + 1]->mesh->checkerTexture = true;
								}
								else {
									compList[j]->mesh->SetTexture(auxiliarTexture);
									if (compList[j + 1] != nullptr && compList[j + 1]->type == ComponentType::MESH) compList[j + 1]->mesh->checkerTexture = false;
								}
							}
						}

						if (j != 1 && compList[j]->mesh->checkerTexture)
						{
							compList[j]->mesh->SetCheckerBoxTexture();

							for (int k = 0; k < compList.size(); k++)
							{
								if (compList[k]->type == ComponentType::TEXTURE)
								{
									compList[k]->texture->SetWidth(128);
									compList[k]->texture->SetHeight(128);
								}
							}

						}
						else if (j != 1) 
						{
							compList[j]->mesh->SetTexture(auxiliarTexture);

							for (int k = 0; k < compList.size(); k++)
							{
								if (compList[k]->type == ComponentType::TEXTURE)
								{
									compList[k]->texture->SetWidth(auxiliarTexture->width);
									compList[k]->texture->SetHeight(auxiliarTexture->height);
								}
							}
						}
					}

					if (compList[j]->type == ComponentType::TEXTURE)
					{

						ImGui::Text("Texture");
						ImGui::Text("	Width: %d", compList[j]->texture->GetWidth());
						ImGui::SameLine();
						ImGui::Text("		Height: %d", compList[j]->texture->GetHeight());

					}

				}
						ImGui::Separator();
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
