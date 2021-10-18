#pragma once

#include "Globals.h"
#include "UiWindow.h"

class Application;

class UiMainMenu : public UiWindow
{
public:
	Application* App;

	UiMainMenu(Application* parent, bool start_enabled = false);

	~UiMainMenu();

	bool Start();

	 update_status PreUpdate(float dt);
	 update_status Update(float dt);
	 update_status PostUpdate(float dt);

	 bool CleanUp();


public:
	bool active;
};