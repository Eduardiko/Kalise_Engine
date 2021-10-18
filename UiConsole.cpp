#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "UiConsole.h"

UiConsole::UiConsole(Application* app, bool start_enabled) : UiWindow(app, start_enabled)
{
}

// Destructor
UiConsole::~UiConsole()
{
}

// Called before render is available
bool UiConsole::Start()
{
	bool ret = true;

	showConfig = true;

	activeBox = true;
	initialBrightness = 5;
	initialWidth = 1280;
	initialHeight = 1080;
	fullscreen = false;
	return ret;
}



update_status UiConsole::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;



	return ret;
}

update_status UiConsole::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	

	if (ImGui::Begin("Configuration"))
	{
		ImGui::Text("Options");
		if (ImGui::CollapsingHeader("Application"))
		{
			
			
			/*	char title[25];
			
			sprintf_s(title, 25, "Framerate %.1f", fps_log[(fps_log.size()) - 1]);
			sprintf_s(title, 25, "Framerate %.1f", fps_log[(fps_log.size()) - 1]);
			ImGui::PlotHistogram("");
			ImGui::PlotHistogram("##framerate", title, IM_ARRAYSIZE(fps_log), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80.0f));
			ImGui::PlotHistogram("##framerate", fps_log, IM_ARRAYSIZE(fps_log), 0, title, 0.0f, 100.0f, ImVec2(310, 100));

			*/
		}
	
		if (ImGui::CollapsingHeader("Window"))
		{
			ImGui::Checkbox("Active", &activeBox);
			ImGui::Text("Icon:");
			ImGui::SliderInt("Brightness", &initialBrightness, 0, 10);
			ImGui::SliderInt("Width", &initialWidth, 0, 3840);
			ImGui::SliderInt("Height", &initialHeight, 0, 2160);
			ImGui::Text("Refresh rate:");

			if (ImGui::Checkbox("Fullscreen", &fullscreen))
				//App->window->SetFullscreen(fullscreen);
		
			

		}

		ImGui::End();
	}

	return ret;
}

update_status UiConsole::PostUpdate(float dt)
{

	update_status ret = UPDATE_CONTINUE;


	return ret;
}


bool UiConsole::CleanUp()
{

	bool ret = true;


	return ret;
}