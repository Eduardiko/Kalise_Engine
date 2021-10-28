#pragma once

#include "Module.h"
#include "SDL.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

#include "UiWindow.h"

#include "UiMainMenu.h"
#include "UiConfiguration.h"

class Application;

class UiManager : public Module
{
public:

	UiManager(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~UiManager();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void LoadScene(const char* path);

	void MainMenuTest();

	void SetTitle(const char* title);

	bool showcase = true;

public:

	std::vector<UiWindow*> windowList;
	void AddWindow(UiWindow* win);

	UiMainMenu* mainMenu;
	UiConfiguration* config;

};
