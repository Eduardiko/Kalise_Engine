#pragma once

#include "Globals.h"
#include "Application.h"
#include "Texture.h"

#include "UiWindow.h"

class Application;

class UiObjects : public UiWindow
{
public:
	Application* App;

	UiObjects(Application* app, bool start_enabled = false);

	~UiObjects();

	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	Texture* auxiliarTexture;

	bool CleanUp();

public:
	bool active;

};