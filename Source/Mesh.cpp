//#include "Globals.h"
//#include "Mesh.h"
//
//#include "glew.h"
//#include <gl/GL.h>
//#include <gl/GLU.h>
//
//// ------------------------------------------------------------
//Mesh::Mesh() : vertexBuffer(-1), vertexCount(-1), vertices(nullptr), indexBuffer(-1), indexCount(-1), indices(nullptr),
//normalsBuffer(-1)
//{
//}
//
//Mesh::~Mesh()
//{
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glDeleteBuffers(1, &vertexBuffer);
//	delete vertices;
//	vertices = nullptr;
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	glDeleteBuffers(1, &indexBuffer);
//	delete indices;
//	indices = nullptr;
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glDeleteBuffers(1, &normalsBuffer);
//	delete normals;
//	normals = nullptr;
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glDeleteBuffers(1, &textureBuffer);
//}
//
//void Mesh::InitBuffers()
//{
//	//Vertex
//	glGenBuffers(1, (GLuint*)&vertexBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 3, vertices, GL_STATIC_DRAW);
//
//	//Normals
//	glGenBuffers(1, &normalsBuffer);
//	glBindBuffer(GL_NORMAL_ARRAY, normalsBuffer);
//	glBufferData(GL_NORMAL_ARRAY, sizeof(float) * vertexCount * 3, normals, GL_STATIC_DRAW);
//
//	// Textures
//	glGenBuffers(1, &textureBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, textureCoordinates, GL_STATIC_DRAW);
//
//	//Indices
//	glGenBuffers(1, &indexBuffer);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indexCount, indices, GL_STATIC_DRAW);
//}
//
//void Mesh::Render() const
//{
//	//textures
//	//glBindBuffer(GL_ARRAY_BUFFER, textureBuf);
//	//glTexCoordPointer(2, GL_FLOAT, 0, NULL);
//	//glBindTexture(GL_TEXTURE_2D, textureID);
//
//	//glPushMatrix();
//	//glMultMatrixf(transform.M);
//
//	//if (drawFaceNormals) DrawFaceNormals();
//	//if (drawVertexNormals) DrawVertexNormals();
//
//	//glPopMatrix();
//}
//
//void Mesh::InnerRender() const
//{
//	glPointSize(5.0f);
//
//	glBegin(GL_POINTS);
//
//	glVertex3f(0.0f, 0.0f, 0.0f);
//
//	glEnd();
//
//	glPointSize(1.0f);
//}
//
//void Mesh::DrawVertexNormals() const
//{
//	if (normalsBuffer == -1)
//		return;
//
//	float normal_lenght = 0.5f;
//
//	//vertices normals
//	glBegin(GL_LINES);
//	for (size_t i = 0, c = 0; i < vertexCount * 3; i += 3, c += 4)
//	{
//		glColor3f(0.85f, 0.0f, 0.85f);
//		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
//
//		glVertex3f(vertices[i] + (normals[i] * normal_lenght),
//			vertices[i + 1] + (normals[i + 1] * normal_lenght),
//			vertices[i + 2] + (normals[i + 2]) * normal_lenght);
//	}
//
//	glColor3f(1.0f, 1.0f, 1.0f);
//	glEnd();
//}
//
//void Mesh::DrawFaceNormals() const
//{
//	if (normalsBuffer == -1)
//		return;
//
//	//vertices normals
//	glBegin(GL_LINES);
//	for (size_t i = 0; i < vertexCount * 3; i += 3)
//	{
//		glColor3f(0.0f, 0.85f, 1.0f);
//		float vx = (vertices[i] + vertices[i + 3] + vertices[i + 6]) / 3;
//		float vy = (vertices[i + 1] + vertices[i + 4] + vertices[i + 7]) / 3;
//		float vz = (vertices[i + 2] + vertices[i + 5] + vertices[i + 8]) / 3;
//
//		float nx = (normals[i] + normals[i + 3] + normals[i + 6]) / 3;
//		float ny = (normals[i + 1] + normals[i + 4] + normals[i + 7]) / 3;
//		float nz = (normals[i + 2] + normals[i + 5] + normals[i + 8]) / 3;
//
//		glVertex3f(vx, vy, vz);
//
//		glVertex3f(vx + (normals[i] * 0.5f),
//			vy + (normals[i + 1] * 0.5f),
//			vz + (normals[i + 2]) * 0.5f);
//	}
//
//	glColor3f(1.0f, 1.0f, 1.0f);
//
//	glEnd();
//}