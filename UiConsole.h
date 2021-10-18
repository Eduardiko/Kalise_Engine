#pragma once

#include "Globals.h"
#include "UiWindow.h"

class Application;

class UiConsole : public UiWindow
{
public:
	Application* App;

	UiConsole(Application* parent, bool start_enabled = false);

	~UiConsole();

	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	bool CleanUp();


public:
	bool active;
	bool showConfig;
};