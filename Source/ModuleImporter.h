#pragma once

#include "Module.h"
#include "Mesh.h"

class Application;
class aiMesh;

class ModuleImporter : public Module
{
public:
	ModuleImporter(Application* app, bool start_enabled = true);
	virtual ~ModuleImporter();

	bool Init();
	bool Start();
	bool CleanUp();

	void ImportScene(const char* path);
	Mesh* ImportModel(aiMesh* aimesh);

	std::vector<Mesh*> meshList;

};