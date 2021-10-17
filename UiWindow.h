#pragma once

#include "Globals.h"

class Application;

class UiWindow
{
public:
	Application* App;

	UiWindow(Application* parent, bool start_enabled = false) : App(parent), active(start_enabled) {}

	virtual ~UiWindow() {}

	virtual bool Start() { return true; }

	virtual update_status PreUpdate() { return update_status::UPDATE_CONTINUE; }
	virtual update_status Update() { return update_status::UPDATE_CONTINUE; }
	virtual update_status PostUpdate() { return update_status::UPDATE_CONTINUE; }

	virtual bool CleanUp() { return true; }


public:
	bool active;
};