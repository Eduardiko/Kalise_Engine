#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleUI::~ModuleUI()
{
}

// Called before render is available
bool ModuleUI::Init()
{
    // Application init: create a dear imgui context, setup some options, load fonts
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;


    // Application main loop

    ImGui_ImplOpenGL2_Init();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);

    ImGui::StyleColorsClassic;

	return true;
}



update_status ModuleUI::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	
	ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Gui Demo"))
				showcase = !showcase;

			if(ImGui::MenuItem("Documentation"))
				App->RequestBrowser("https://desktop.github.com/");
			
			if(ImGui::MenuItem("Download Latest")) {}

			if(ImGui::MenuItem("Report a bug")) {}

			if(ImGui::MenuItem("About")) {}
			
			ImGui::EndMenu();
		}
	ImGui::EndMainMenuBar();

	ImGui::ShowDemoWindow();
	ImGui::Render();

	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

void ModuleUI::SetTitle(const char* title)
{

}

bool ModuleUI::CleanUp()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    /*ImGui::End();*/
    return true;
}