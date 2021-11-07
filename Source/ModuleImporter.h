#pragma once

#include "Module.h"
#include "Mesh.h"

class Application;
class aiMesh;
class aiScene;

class ModuleImporter : public Module
{
public:
	ModuleImporter(Application* app, bool start_enabled = true);
	virtual ~ModuleImporter();

	bool Init();
	bool Start();
	bool CleanUp();

	std::vector<Mesh*> ImportScene(const char* path);
	Mesh* ImportModel(aiMesh* aimesh);

	Texture* LoadTexture(const char* path, const char* name);
	Texture* LoadTexture(const aiScene* scene, aiMesh* mesh, const char* path, const char* name);

	std::vector<Mesh*> meshList;

};