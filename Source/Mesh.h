#pragma once

#include "Texture.h"
#include "glmath.h"
#include <vector>

class Mesh
{
public:

	Mesh();
	virtual	~Mesh();

	void InitBuffers();

	virtual void Render() const;
	virtual void InnerRender() const;
	void DrawVertexNormals() const;
	void DrawFaceNormals() const;

	void InitRender() const;
	void EndRender() const;

	void DrawVertices() const;
	void DrawNormals() const;
	void DrawTexture() const;
	void BindIndices() const;
	void ApplyTransform() const;
	void DrawElements() const;

	void SetTexture(Texture* texture);
	void SetDefaultTexture();

	Texture* GetTexture();

public:
	unsigned int indexBuffer = 0;
	int indexCount = -1;
	unsigned int* indices = nullptr;

	unsigned int vertexBuffer = 0;
	int vertexCount = -1;
	float* vertices = nullptr;

	unsigned int normalsBuffer = 0;
	float* normals = nullptr;

	unsigned int textureID = -1;
	unsigned int textureBuffer = 0;
	float* textureCoordinates = nullptr;
	Texture* texture = nullptr;

	mat4x4 transform;
	bool wire;
	bool drawFaceNormals = true;
	bool drawVertexNormals = true;

	bool checkerTexture = false;
	
};