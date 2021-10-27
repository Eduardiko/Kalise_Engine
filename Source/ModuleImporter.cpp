#include "Globals.h"
#include "Application.h"
#include "ModuleImporter.h"

#include "scene.h"
#include "cimport.h"
#include "postprocess.h"

ModuleImporter::ModuleImporter(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleImporter::~ModuleImporter()
{
}

bool ModuleImporter::Init()
{
	bool ret = true;

	return ret;
}

bool ModuleImporter::Start()
{
	//ImportScene("Assets/warrior.fbx");
	ImportScene("Assets/BakerHouse.fbx");
	return true;
}

bool ModuleImporter::CleanUp()
{


	return true;
}

void ModuleImporter::ImportScene(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			meshList.push_back(ImportModel(scene->mMeshes[i]));
		}
		aiReleaseImport(scene);
	}
	else
	{
		//LOG missing
	}

}

Mesh* ModuleImporter::ImportModel(aiMesh* aiMesh)
{
	Mesh* mesh = new Mesh();
	mesh->vertexCount = aiMesh->mNumVertices;
	mesh->vertices = new float[mesh->vertexCount * 3];
	memcpy(mesh->vertices, aiMesh->mVertices, sizeof(float) * mesh->vertexCount * 3);


	if (aiMesh->HasFaces())
	{
		mesh->indexCount = aiMesh->mNumFaces * 3;
		mesh->indices = new uint[mesh->indexCount];
		for (uint j = 0; j < aiMesh->mNumFaces; j++)
		{
			if (aiMesh->mFaces[j].mNumIndices != 3)
			{
				//LOG Missing
			}
			else
			{
				memcpy(&mesh->indices[j * 3], aiMesh->mFaces[j].mIndices, sizeof(uint) * 3);
			}
		}

		mesh->normals = new float[aiMesh->mNumVertices * 3]();

		for (uint i = 0; i < aiMesh->mNumVertices; i += 3)
		{
			if (aiMesh->HasNormals())
			{
				mesh->normals[i] = aiMesh->mNormals[i].x;
				mesh->normals[i + 1] = aiMesh->mNormals[i].y;
				mesh->normals[i + 2] = aiMesh->mNormals[i].z;
			}
		}

		mesh->textureCoordinates = new float[mesh->vertexCount * 2]();

		if (aiMesh->mTextureCoords[0])
		{
			for (uint i = 0; i < aiMesh->mNumVertices; i++)
			{
				mesh->textureCoordinates[i * 2] = aiMesh->mTextureCoords[0][i].x;
				mesh->textureCoordinates[i * 2 + 1] = aiMesh->mTextureCoords[0][i].y;
			}
		}

		meshList.push_back(mesh);

		return mesh;
	}

	return nullptr;
}