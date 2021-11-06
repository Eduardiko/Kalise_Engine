#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleImporter.h"
#include "UiManager.h"
#include "BaseScene.h"
#include <vector>

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleImporter* importer;
	UiManager* ui;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	BaseScene* scene;

private:

	Timer	ms_timer;
	float	dt;

	std::vector<Module*> moduleList;

	std::string appName = "Kalise Engine";
	std::string organizationName = "UPC CITM";

	int frameStart;
	Uint32 sTicks;

public:
	int maxFps = 60;
	float currentFps;

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void RequestBrowser(LPCSTR link);

	void SetName(std::string name, int id);
	const char* GetName(int id);

	inline const float GetFps() { return (float)currentFps; }


private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};