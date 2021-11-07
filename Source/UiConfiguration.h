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

	void swapActive();

public:
	bool active;
	bool showConfig;

	bool activeBox;

	int initialBrightness;

	bool fullscreen;
	bool resizable;
	bool borderless;


	Application* app;
	std::vector<float> fps_log;
	std::vector<float> ms_log;
	int maxFps;

	int fpsCounter;

	void getCaps(bool& threeD, bool& altiVec, bool& avx, bool& avx2, bool& mmx, bool& rdtsc, bool& sse, bool& sse2, bool& sse3, bool& sse41, bool& sse42);
	

};