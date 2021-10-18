#include "Globals.h"
#include "Application.h"
#include "UiWindowManager.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

UiWindowManager::UiWindowManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	mainMenu = new UiMainMenu(app, true);
	console = new UiConsole(app, true);

	AddWindow(mainMenu);
	AddWindow(console);

}

// Destructor
UiWindowManager::~UiWindowManager()
{
	
	for (int i = 0; i <= windowList.size() - 1; i++)
	{
		delete windowList[i];
	}
	
}

// Called before render is available
bool UiWindowManager::Init()
{
	bool ret = true;

    // Application init: create a dear imgui context, setup some options, load fonts
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;


    // Application main loop

    ImGui_ImplOpenGL2_Init();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);

	std::vector<UiWindow*>::iterator i = windowList.begin();
	
	while (i != windowList.end() && ret)
	{
		ret = (*i)->Start();
		i++;
	}

    ImGui::StyleColorsClassic;

	return ret;
}



update_status UiWindowManager::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();


	return ret;
}

update_status UiWindowManager::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	std::vector<UiWindow*>::iterator i = windowList.begin();

	while (i != windowList.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*i)->PreUpdate(dt);
		if (ret == UPDATE_STOP) return UPDATE_STOP;
		ret = (*i)->Update(dt);
		if (ret == UPDATE_STOP) return UPDATE_STOP;
		ret = (*i)->PostUpdate(dt);
		if (ret == UPDATE_STOP) return UPDATE_STOP;
		i++;
	}

	//MainMenuTest();

	return ret;
}

update_status UiWindowManager::PostUpdate(float dt)
{
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	update_status ret = UPDATE_CONTINUE;


	return ret;
}

void UiWindowManager::SetTitle(const char* title)
{

}

bool UiWindowManager::CleanUp()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
	
	bool ret = true;
	
    return ret;
}

void UiWindowManager::MainMenuTest()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("Gui Demo"))
			showcase = !showcase;

		if (ImGui::MenuItem("Documentation"))
			App->RequestBrowser("https://desktop.github.com/");

		if (ImGui::MenuItem("Download Latest")) {}

		if (ImGui::MenuItem("Report a bug")) {}

		if (ImGui::MenuItem("About")) {}

		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}

void UiWindowManager::AddWindow(UiWindow* win)
{
	windowList.push_back(win);
}