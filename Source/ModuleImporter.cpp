#include "Globals.h"
#include "Application.h"
#include "ModuleImporter.h"
#include "GameObject.h"

#include "il.h"
#include "ilu.h"
#include "ilut.h"

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

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	return ret;
}

bool ModuleImporter::Start()
{

	return true;
}

bool ModuleImporter::CleanUp()
{

	return true;
}

std::vector<Mesh*> ModuleImporter::ImportScene(const char* path)
{
	std::vector<Mesh*> meshList;
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			Mesh* mesh = ImportModel(scene->mMeshes[i]);
			meshList.push_back(mesh);
			Texture* Tex = LoadTexture(scene, scene->mMeshes[i], "Assets/BakerHouse.png", "BakerHouse");
			mesh->SetTexture(Tex);

		}
		aiReleaseImport(scene);
	}

	return meshList;
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

		return mesh;
	}

	return nullptr;
}

Texture* ModuleImporter::LoadTexture(const char* path, const char* name)
{
	uint id = 0;
	ilGenImages(1, &id);
	ilBindImage(id);

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	Texture* texture = new Texture();

	if (ilLoadImage(path))
	{
		if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
		{
			texture->id = id;
			texture->name = name;
			texture->data = ilGetData();
			texture->width = ilGetInteger(IL_IMAGE_WIDTH);
			texture->height = ilGetInteger(IL_IMAGE_HEIGHT);
			texture->format = texture->formatUnsigned = ilGetInteger(IL_IMAGE_FORMAT);
			texture->path = path;
		}
	}

	return texture;
}

Texture* ModuleImporter::LoadTexture(const aiScene* scene, aiMesh* mesh, const char* path, const char* name)
{
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	aiString texPath;
	aiGetMaterialTexture(material, aiTextureType::aiTextureType_DIFFUSE, mesh->mMaterialIndex, &texPath);

	Texture* texture = new Texture();

	texture = LoadTexture(path, name);
	return texture;
}