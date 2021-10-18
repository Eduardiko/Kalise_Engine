#include "Globals.h"
#include "Application.h"
#include "UiConsole.h"

UiConsole::UiConsole(Application* app, bool start_enabled) : UiWindow(app, start_enabled)
{
}

// Destructor
UiConsole::~UiConsole()
{
}

// Called before render is available
bool UiConsole::Start()
{
	bool ret = true;

	showConfig = true;

	return ret;
}



update_status UiConsole::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;



	return ret;
}

update_status UiConsole::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (ImGui::Begin("Configuration"))
	{
		
		ImGui::End();
	}

	return ret;
}

update_status UiConsole::PostUpdate(float dt)
{

	update_status ret = UPDATE_CONTINUE;


	return ret;
}


bool UiConsole::CleanUp()
{

	bool ret = true;


	return ret;
}