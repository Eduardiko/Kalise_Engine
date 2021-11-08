#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "BaseScene.h"
#include "UiConfiguration.h"
#include <gl/GL.h>

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

	active = false;

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
	
	if (!active) return ret;

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

		
		ImGui::Text("Mouse Pos X: %d", app->input->GetMouseX());
		ImGui::Text("Mouse Pos Y: %d", app->input->GetMouseY());

		if (ImGui::BeginMenu("Open GL"))
		{
			static bool depth = true;
			static bool cull = true;
			static bool lighting = true;
			static bool materialColor = true;
			static bool texture2D = true;
			static bool wired = false;

			ImGui::Checkbox("GL_DEPTH_TEST", &depth);
			ImGui::Checkbox("GL_CULL_FACE", &cull);
			ImGui::Checkbox("GL_LIGHTING", &lighting);
			ImGui::Checkbox("GL_COLOR_MATERIAL", &materialColor);
			ImGui::Checkbox("GL_TEXTURE_2D", &texture2D);

			if (!depth)
				glDisable(GL_DEPTH_TEST);
			else
				glEnable(GL_DEPTH_TEST);

			if (!cull)
				glDisable(GL_CULL_FACE);
			else
				glEnable(GL_CULL_FACE);

			if (!lighting)
				glDisable(GL_LIGHTING);
			else
				glEnable(GL_LIGHTING);

			if (!materialColor)
				glDisable(GL_COLOR_MATERIAL);
			else
				glEnable(GL_COLOR_MATERIAL);

			if (!texture2D)
				glDisable(GL_TEXTURE_2D);
			else
				glEnable(GL_TEXTURE_2D);

			ImGui::EndMenu();
		}

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

		SDL_version v;
		SDL_GetVersion(&v);
		int major, minor, patch;
		major = v.major;
		minor = v.minor;
		patch = v.patch;
	
		ImGui::Text("SDL Version:");
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
		ImGui::Text("%d.%d.%d", major, minor, patch);
		ImGui::PopStyleColor();

		ImGui::Separator();

		ImGui::Text("CPUs:");
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
		ImGui::Text("%d (Cache:%dkb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
		ImGui::PopStyleColor();

		ImGui::Text("System RAM:");	
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
		ImGui::Text("%dGb", SDL_GetSystemRAM() / 1000);
		ImGui::PopStyleColor();

		ImGui::Text("Caps:");
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));

		bool threeD, altiVec, avx, avx2, mmx, rdtsc, sse, sse2, sse3, sse41, sse42;
		getCaps(threeD, altiVec, avx, avx2, mmx, rdtsc, sse, sse2, sse3, sse41, sse42);
		ImGui::Text("%s %s %s %s %s %s", threeD ? "3DNow," : "", altiVec ? "AltiVec," : "", avx ? "AVX," : "", avx2 ? "AVX2," : "", mmx ? "MMX," : "", rdtsc ? "RDTSC," : "");
		ImGui::Text("%s %s %s %s %s", sse ? "SSE," : "", sse2 ? "SSE2," : "", sse3 ? "SSE3," : "", sse41 ? "SSE41," : "", sse42 ? "SSE42" : "");
		ImGui::PopStyleColor();

		ImGui::Separator();

		ImGui::Text("GPU:", SDL_GetSystemRAM());
		ImGui::SameLine();

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

void UiConfiguration::swapActive()
{
	active = !active;
}

void UiConfiguration::getCaps(bool& threeD, bool& altiVec, bool& avx, bool& avx2, bool& mmx, bool& rdtsc, bool& sse, bool& sse2, bool& sse3, bool& sse41, bool& sse42)
{
	threeD = (bool)SDL_Has3DNow();
	altiVec = (bool)SDL_HasAltiVec();
	avx = (bool)SDL_HasAVX();
	avx2 = (bool)SDL_HasAVX2();
	mmx = (bool)SDL_HasMMX();
	rdtsc = (bool)SDL_HasRDTSC();
	sse = (bool)SDL_HasSSE();
	sse2 = (bool)SDL_HasSSE2();
	sse3 = (bool)SDL_HasSSE3();
	sse41 = (bool)SDL_HasSSE41();
	sse42 = (bool)SDL_HasSSE42();
}
