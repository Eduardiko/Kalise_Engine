#include "Globals.h"
#include "Application.h"
#include "UiMainMenu.h"

UiMainMenu::UiMainMenu(Application* app, bool start_enabled) : UiWindow(app, start_enabled)
{
}

// Destructor
UiMainMenu::~UiMainMenu()
{
}

// Called before render is available
bool UiMainMenu::Start()
{
	bool ret = true;

	showDemo = false;

	return ret;
}



update_status UiMainMenu::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	

	return ret;
}

update_status UiMainMenu::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Quit", "ESC"))
			ret = UPDATE_STOP;


		ImGui::EndMenu();
	}

	ImGui::BeginMenu("View");

	/*if (ImGui::BeginMenu("View"))
	{
			// Here goes every window to show/not show
	}*/

	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("Gui Demo"))
			showDemo = !showDemo;

		if (ImGui::MenuItem("Documentation"))
			App->RequestBrowser("https://desktop.github.com/");

		if (ImGui::MenuItem("Download Latest")) {}

		if (ImGui::MenuItem("Report a bug")) {}

		if (ImGui::MenuItem("About")) {}

		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();

	if(showDemo) ImGui::ShowDemoWindow();

	return ret;
}

update_status UiMainMenu::PostUpdate(float dt)
{

	update_status ret = UPDATE_CONTINUE;


	return ret;
}


bool UiMainMenu::CleanUp()
{

	bool ret = true;


	return ret;
}