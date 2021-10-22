#pragma once

#include "Globals.h"
#include "UiWindow.h"


class Application;

class UiConfiguration : public UiWindow
{
public:
	Application* App;

	UiConfiguration(Application* parent, bool start_enabled = false);

	~UiConfiguration();

	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	bool CleanUp();


public:
	bool active;
	bool showConfig;

	bool activeBox;

	int initialBrightness;

	bool fullscreen;
	bool resizable;
	bool borderless;


	Application* app;
	//std::vector<UiWindow*> fps_log;
	//int fps_log[];

};