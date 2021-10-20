#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "UiConsole.h"

UiConsole::UiConsole(Application* app_, bool start_enabled) : UiWindow(app, start_enabled)
{
	app = app_;
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

	fullscreen = false;
	borderless = false;
	resizable = false;

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
			ImGui::SliderInt("Width", &app->window->screen_surface->w, 0, 1920);
			ImGui::SliderInt("Height", &app->window->screen_surface->h, 0, 1080);
			if(resizable) SDL_SetWindowSize(app->window->window, app->window->screen_surface->w, app->window->screen_surface->h);
			ImGui::Text("Refresh rate: %.3f", ImGui::GetIO().Framerate);

			if (ImGui::Checkbox("Fullscreen", &fullscreen))
				app->window->SetFullscreen(fullscreen);
			ImGui::SameLine();
			if (ImGui::Checkbox("Resizable", &resizable));
			{
				if (resizable) SDL_SetWindowResizable(app->window->window, SDL_TRUE);
				
				if (!resizable)	SDL_SetWindowResizable(app->window->window, SDL_FALSE);
				
			}

			if (ImGui::Checkbox("Borderless", &borderless));
			{
				if (borderless) SDL_SetWindowBordered(app->window->window, SDL_FALSE);
				if (!borderless) SDL_SetWindowBordered(app->window->window, SDL_TRUE);
			}
				

		}

		

		if (ImGui::CollapsingHeader("Hardware"))
		{
			ImGui::Text("SDL Version:");
			ImGui::Separator();
			ImGui::Text("CPUs: %d (Cache: %dkb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
			ImGui::Text("System RAM: %dGb", SDL_GetSystemRAM());	
			
			ImGui::Separator();
			ImGui::Text("GPU:", SDL_GetSystemRAM());
			ImGui::Text("Brand:", SDL_GetSystemRAM());
			ImGui::Text("VRAM Budget:", SDL_GetSystemRAM());
			ImGui::Text("VRAM Usage: %dGb", SDL_GetSystemRAM());
			ImGui::Text("System RAM: %dGb", SDL_GetSystemRAM());


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