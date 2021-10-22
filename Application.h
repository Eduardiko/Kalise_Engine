#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "UiWindowManager.h"
#include <vector>

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	UiWindowManager* ui;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;

private:

	Timer	ms_timer;
	float	dt;
	//p2List<Module*> list_modules;
	std::vector<Module*> list_modules;

	std::string appName = "Kalise Engine";
	std::string organizationName = "UPC CITM";

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void RequestBrowser(LPCSTR link);

	void SetName(std::string name, int id);
	const char* GetName(int id);

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};