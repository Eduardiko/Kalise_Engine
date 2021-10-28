#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	importer = new ModuleImporter(this);
	ui = new UiManager(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(importer);
	AddModule(ui);
	
	// Scenes

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{

	for(int i = 0; i <= moduleList.size() - 1; i++)
	{
		delete moduleList[i];
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules

	std::vector<Module*>::iterator item = moduleList.begin();

	while (item != moduleList.end() && ret)
	{
		ret = (*item)->Init();
		item++;
	}



	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = moduleList.begin();

	while (item != moduleList.end() && ret)
	{
		ret = (*item)->Start();
		item++;
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	frameStart = ms_timer.Read();
	sTicks = SDL_GetTicks();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	int frameEnd = ms_timer.Read();

	int deltaMilliseconds = frameEnd - frameStart;
	dt = (float)deltaMilliseconds / 1000.0f;

	float targetDt = 1000.0f / (float)maxFps;
	if (dt < targetDt) {
		SDL_Delay(targetDt - dt);
		dt = targetDt;
	}

	Uint32 endTicks = SDL_GetTicks();
	float frameTime = (endTicks - sTicks) / 1000.0f;
	currentFps = 1.0f / frameTime;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	//p2List_item<Module*>* item = moduleList.getFirst();
	std::vector<Module*>::iterator item = moduleList.begin();

	while(item != moduleList.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PreUpdate(dt);
		item++;
	}

	item = moduleList.begin();

	while(item != moduleList.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->Update(dt);
		item++;
	}

	item = moduleList.begin();

	while(item != moduleList.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PostUpdate(dt);
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = 0; i <= moduleList.size() - 1; i++)
	{
		ret = moduleList[i]->CleanUp();
	}
	return ret;
}

void Application::RequestBrowser(LPCSTR link)
{
	ShellExecuteA(NULL, "open", link, NULL, NULL, SW_SHOWNORMAL);
}

void Application::AddModule(Module* mod)
{
	moduleList.push_back(mod);
}

void Application::SetName(std::string name, int id)
{

	if (!name.empty())
	{

		if (id == 0)
		{
			appName = name;
			window->SetTitle(name.c_str());
		}

		if (id == 1) organizationName = name;
	}

}

const char* Application::GetName(int id)
{
	if (id == 0) return appName.c_str();
	if (id == 1) return organizationName.c_str();
}
