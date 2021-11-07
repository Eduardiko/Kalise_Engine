#include "Globals.h"
#include "Application.h"
#include "ModuleImporter.h"
#include "GameObject.h"
#include "UiManager.h"
#include "imgui.h"
#include "glew.h"
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

UiManager::UiManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	mainMenu = new UiMainMenu(app, true);
	config = new UiConfiguration(app, true);
	objects = new UiObjects(app, true);

	AddWindow(mainMenu);
	AddWindow(config);
	AddWindow(objects);

}

// Destructor
UiManager::~UiManager()
{
	
	for (int i = 0; i <= windowList.size() - 1; i++)
	{
		delete windowList[i];
	}
	
}

// Called before render is available
bool UiManager::Init()
{
	bool ret = true;

    // Application init: create a dear imgui context, setup some options, load fonts
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


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

bool UiManager::Start()
{
	glewInit();


	return true;
}

update_status UiManager::PreUpdate(float dt)
{

	update_status ret = UPDATE_CONTINUE;

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();


	return ret;
}

update_status UiManager::Update(float dt)
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

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) config->active = !config->active;
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) objects->active = !objects->active;


	return ret;
}

update_status UiManager::PostUpdate(float dt)
{
	//grid
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	float d = 100.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}
	glEnd();

	
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	update_status ret = UPDATE_CONTINUE;


	return ret;
}

void UiManager::SetTitle(const char* title)
{

}

bool UiManager::CleanUp()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
	
	bool ret = true;
	
    return ret;
}

void UiManager::LoadScene(const char* path, const char* name)
{

	std::vector<Mesh*> meshList = App->importer->ImportScene(path);
	GameObject* object = new GameObject(name);

	for (int i = 0; i < meshList.size(); i++) {
			object->CreateComponent(ComponentType::MESH, meshList[i]);
	}
		
	App->scene->objectList.push_back(object);

	for (int i = 0; i < App->scene->objectList.size(); i++) {
		for (auto component : App->scene->objectList[i]->GetComponents())
		{
			App->scene->parent = App->scene->objectList[i];

			if (component->GetType() == ComponentType::MESH)
				component->GetMesh()->InitBuffers();
		}
	}
}

void UiManager::MainMenuTest()
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

void UiManager::AddWindow(UiWindow* win)
{
	windowList.push_back(win);
}