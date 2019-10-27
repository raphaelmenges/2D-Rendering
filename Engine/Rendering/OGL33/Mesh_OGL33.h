#ifndef MESH_OGL33_H_
#define MESH_OGL33_H_

#include "../Mesh.h"

#include "../../External/gl_core_3_3.h"
#include <GLFW/glfw3.h>

class Mesh_OGL33 : public Mesh
{
public:

	/* Constructor */
	Mesh_OGL33();

	/* Destructor */
	virtual ~Mesh_OGL33();

	/* OpenGL handles */
	_uint getVerticesBufferHandle() const { return mVertices; }
	_uint getTextureCoordinateBufferHandle() const { return mTextureCoordinates; }
	_uint getVertexCount() const { return mVertexCount; }

protected:

	/* Protected initialization method */
	virtual void init(vector<_float> const * pVertices, vector<_float> const * pTextureCoordinates);

	_uint mVertices;
	_uint mTextureCoordinates;
};

#endif
