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
	
	fpsCounter = 0;

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
	
	if (fpsCounter < 99)
		fpsCounter++;
	else
	{
		fps_log.erase(fps_log.begin());
		ms_log.erase(ms_log.begin());
	}
	
	fps_log.push_back(ImGui::GetIO().Framerate);
	ms_log.push_back(1000.0f / ImGui::GetIO().Framerate);


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
		ImGui::Checkbox("Active", &activeBox);

		static char name[50] = "";
		strcpy_s(name, 50, app->GetName(0));
		ImGui::InputText("App Name", name, IM_ARRAYSIZE(name));
		strcpy_s(name, 50, app->GetName(1));
		ImGui::InputText("Organization Name", name, IM_ARRAYSIZE(name));
		
		maxFps = app->maxFps;
		if (ImGui::SliderInt("Max FPS", &maxFps, 1, 120))
		{
			app->maxFps = maxFps;
		}

		/////// Limit framerate counter
		ImGui::Text("Limit Framerate:");
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
		ImGui::Text("%d", app->maxFps);
		ImGui::PopStyleColor();

		std::string title = "Framerate ";
		title += std::to_string(ImGui::GetIO().Framerate);
		ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title.c_str(), 0.0f, 100.0f, ImVec2(310.0f, 100.0f));
		
		title = "Milliseconds ";
		title += std::to_string(1000.0f / ImGui::GetIO().Framerate);
		ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title.c_str(), 0.0f, 40.0f, ImVec2(310.0f, 100.0f));


	}
	
	if (ImGui::CollapsingHeader("Window"))
	{
			
		ImGui::Checkbox("Active", &activeBox);
		ImGui::Text("Icon:");
		ImGui::SliderInt("Brightness", &initialBrightness, 0, 10);
		ImGui::SliderInt("Width", &app->window->screen_surface->w, 0, 1920);
		ImGui::SliderInt("Height", &app->window->screen_surface->h, 0, 1080);
		if (resizable) SDL_SetWindowSize(app->window->window, app->window->screen_surface->w, app->window->screen_surface->h);

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
		ImGui::Checkbox("Active", &activeBox);

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