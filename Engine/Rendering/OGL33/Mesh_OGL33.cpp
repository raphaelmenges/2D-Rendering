#include "Mesh_OGL33.h"

Mesh_OGL33::Mesh_OGL33()
{

}

Mesh_OGL33::~Mesh_OGL33()
{
	/* Delete buffers */
	glDeleteBuffers(1, &mVertices);
	glDeleteBuffers(1, &mTextureCoordinates);
}

void Mesh_OGL33::init(vector<_float> const * pVertices, vector<_float> const * pTextureCoordinates)
{
	/* Vertex buffer object on GPU */
	mVertices = 0; // index of VBO
	glGenBuffers(1, &mVertices); // generate VBO
	glBindBuffer(GL_ARRAY_BUFFER, mVertices); // set as current VBO
	glBufferData(GL_ARRAY_BUFFER, pVertices->size() * sizeof(_float), pVertices->data(), GL_STATIC_DRAW); // copy data

	// UV buffer object on GPU
	mTextureCoordinates = 0; // index of VBO
	glGenBuffers(1, &mTextureCoordinates); // generate VBO
	glBindBuffer(GL_ARRAY_BUFFER, mTextureCoordinates); // set as current VBO
	glBufferData(GL_ARRAY_BUFFER, pTextureCoordinates->size() * sizeof(_float), pTextureCoordinates->data(), GL_STATIC_DRAW); // copy data

	/* Save vertex count */
	mVertexCount = static_cast<_uint>(pVertices->size()) / 3;
}
