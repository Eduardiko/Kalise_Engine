#include "Globals.h"
#include "Mesh.h"

#include "glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

// ------------------------------------------------------------
Mesh::Mesh() : transform(IdentityMatrix), wire(false), vertexBuffer(-1), vertexCount(-1), vertices(nullptr), indexBuffer(-1), indexCount(-1), indices(nullptr),
normalsBuffer(-1), textureBuffer(-1), textureID(-1), textureCoordinates(nullptr), normals(nullptr), texture(nullptr), drawFaceNormals(false), drawVertexNormals(false)
{
}

Mesh::~Mesh()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vertexBuffer);
	delete vertices;
	vertices = nullptr;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &indexBuffer);
	delete indices;
	indices = nullptr;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &normalsBuffer);
	delete normals;
	normals = nullptr;

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteBuffers(1, &textureBuffer);
	glDeleteTextures(1, &textureID);
}

void Mesh::InitBuffers()
{
	//Vertex
	glGenBuffers(1, (GLuint*)&vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 3, vertices, GL_STATIC_DRAW);

	//Normals
	glGenBuffers(1, &normalsBuffer);
	glBindBuffer(GL_NORMAL_ARRAY, normalsBuffer);
	glBufferData(GL_NORMAL_ARRAY, sizeof(float) * vertexCount * 3, normals, GL_STATIC_DRAW);

	//Indices
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indexCount, indices, GL_STATIC_DRAW);

	//Textures
	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, textureCoordinates, GL_STATIC_DRAW);

	
}

void Mesh::Render() const
{
	InitRender();
	DrawVertices();
	DrawNormals();
	DrawTexture();
	BindIndices();
	ApplyTransform();
	DrawElements();
	EndRender();
}

void Mesh::InnerRender() const
{
	glPointSize(5.0f);

	glBegin(GL_POINTS);

	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();

	glPointSize(1.0f);
}

void Mesh::DrawVertexNormals() const
{
	if (normalsBuffer == -1)
		return;

	float normal_lenght = 0.5f;

	//vertices normals
	glBegin(GL_LINES);
	for (size_t i = 0, c = 0; i < vertexCount * 3; i += 3, c += 4)
	{
		glColor3f(0.85f, 0.0f, 0.85f);
		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);

		glVertex3f(vertices[i] + (normals[i] * normal_lenght),
			vertices[i + 1] + (normals[i + 1] * normal_lenght),
			vertices[i + 2] + (normals[i + 2]) * normal_lenght);
	}

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();
}

void Mesh::DrawFaceNormals() const
{
	if (normalsBuffer == -1)
		return;

	//vertices normals
	glBegin(GL_LINES);
	for (size_t i = 0; i < vertexCount * 3; i += 3)
	{
		glColor3f(0.0f, 0.85f, 1.0f);
		float vx = (vertices[i] + vertices[i + 3] + vertices[i + 6]) / 3;
		float vy = (vertices[i + 1] + vertices[i + 4] + vertices[i + 7]) / 3;
		float vz = (vertices[i + 2] + vertices[i + 5] + vertices[i + 8]) / 3;

		float nx = (normals[i] + normals[i + 3] + normals[i + 6]) / 3;
		float ny = (normals[i + 1] + normals[i + 4] + normals[i + 7]) / 3;
		float nz = (normals[i + 2] + normals[i + 5] + normals[i + 8]) / 3;

		glVertex3f(vx, vy, vz);

		glVertex3f(vx + (normals[i] * 0.5f),
			vy + (normals[i + 1] * 0.5f),
			vz + (normals[i + 2]) * 0.5f);
	}

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnd();
}

void Mesh::InitRender() const
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Mesh::EndRender() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_NORMAL_ARRAY, 0);
	glBindBuffer(GL_TEXTURE_COORD_ARRAY, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Mesh::DrawVertices() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
}

void Mesh::DrawNormals() const
{
	glBindBuffer(GL_NORMAL_ARRAY, normalsBuffer);
	glNormalPointer(GL_FLOAT, 0, NULL);
}

void Mesh::DrawTexture() const
{
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Mesh::BindIndices() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

void Mesh::ApplyTransform() const
{
	glPushMatrix();
	glMultMatrixf(transform.M);
	glPopMatrix();
}

void Mesh::DrawElements() const
{
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
}

void Mesh::SetTexture(Texture* texture)
{
	if (texture != nullptr && texture->data != nullptr)
	{
		this->texture = texture;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Mesh::SetCheckerBoxTexture()
{

	GLubyte checkerTex[128][128][4];

	for (int i = 0; i < 128; ++i)
	{
		for (int j = 0; j < 128; ++j)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerTex[i][j][0] = (GLubyte)c;
			checkerTex[i][j][1] = (GLubyte)c;
			checkerTex[i][j][2] = (GLubyte)c;
			checkerTex[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerTex);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture* Mesh::GetTexture()
{
	return texture;
}
