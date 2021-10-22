#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "UiConfiguration.h"

UiConfiguration::UiConfiguration(Application* app_, bool start_enabled) : UiWindow(app, start_enabled)
{
	app = app_;
}

// Destructor
UiConfiguration::~UiConfiguration()
{
}

// Called before render is available
bool UiConfiguration::Start()
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



update_status UiConfiguration::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;



	return ret;
}

update_status UiConfiguration::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;
	

	ImGui::Begin("Configuration");
	
	if (ImGui::BeginMenu("Options"))
	{
		if (ImGui::MenuItem("Set Defaults"))
		{

		}
		if (ImGui::MenuItem("Load"))
		{

		}
		if (ImGui::MenuItem("Save"))
		{

		}

		ImGui::EndMenu();
	}

	if (ImGui::CollapsingHeader("Application"))
	{

		static char name[50] = "";
		strcpy_s(name, 50, app->GetName(0));
		ImGui::InputText("App Name", name, IM_ARRAYSIZE(name));
		strcpy_s(name, 50, app->GetName(1));
		ImGui::InputText("Organization Name", name, IM_ARRAYSIZE(name));
		
	
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
	

	return ret;
}

update_status UiConfiguration::PostUpdate(float dt)
{

	update_status ret = UPDATE_CONTINUE;


	return ret;
}


bool UiConfiguration::CleanUp()
{

	bool ret = true;


	return ret;
}