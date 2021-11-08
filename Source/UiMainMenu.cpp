#include "Globals.h"
#include "Application.h"
#include "UiMainMenu.h"

UiMainMenu::UiMainMenu(Application* app, bool start_enabled) : UiWindow(app, start_enabled)
{
	App = app;
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


		if (ImGui::BeginMenu("Load"))
		{
			if (ImGui::MenuItem("Baker House"))
				App->ui->LoadScene("Assets/BakerHouse.fbx", "Baker House");

			if (ImGui::MenuItem("Warrior"))
				App->ui->LoadScene("Assets/warrior.fbx", "Warrior");
			ImGui::EndMenu();
		}

		ImGui::EndMenu();
	}


	if (ImGui::BeginMenu("View"))
	{
		
		ImGui::MenuItem("Configuration", "F1", &App->ui->config->active);
		ImGui::MenuItem("Objects", "F2", &App->ui->objects->active);
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("Gui Demo"))
			showDemo = !showDemo;

		if (ImGui::MenuItem("Latest Release"))
			App->RequestBrowser("https://github.com/Eduardiko/Kalise_Engine");

		if (ImGui::BeginMenu("About"))
		{
			ImGui::Text("Kalise Engine v1.0");
			ImGui::Text("Developed by Eduard Minguell & Marti Davicino");
			ImGui::Text("");
			ImGui::Text("Libraries Used");
			ImGui::BulletText("SDL");
			ImGui::BulletText("ImGui");
			ImGui::BulletText("MathGeoLib");
			ImGui::BulletText("Glew");
			ImGui::BulletText("OpenGL");
			ImGui::BulletText("DevIl");

			ImGui::Text("");
			ImGui::Text("Licenses");
			ImGui::BulletText("MIT License");
			ImGui::BulletText("CopyRight(c) 2021 Eduard Minguell and Marti Davicino");

			ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy \n of this softwareand associated documentation files(the 'Software'), to deal \n in the Software without restriction, including without limitation the rights \n to use, copy, modify, merge, publish, distribute, sublicense, and /or sell \n copies of the Software, and to permit persons to whom the Software is \n furnished to do so, subject to the following conditions :");
			ImGui::Text("");

			ImGui::Text("The above copyright noticeand this permission notice shall be included in all \n copies or substantial portions of the Software.");

			ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR \n IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, \n FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE \n AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER \n LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, \n OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE \n SOFTWARE.");
			ImGui::EndMenu();

		}
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