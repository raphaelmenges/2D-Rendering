#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include <sstream>

#include "../Global.h"
#include "Shader.h"
#include "Primitives.h"
#include "../Math/Math.h"
#include "../Structs/CullingCircle.h"

#include "../External/tiny_obj_loader.h"

enum class PrimitiveMesh
{
	Quad
};

class Mesh
{
public:

	/* Constructor */
	Mesh();

	/* Destructor */
	virtual ~Mesh();

	/* Initialization */
	void init(string path);
	void init(PrimitiveMesh primitiveMesh);

	/* Getter */
	const CullingCircle& getCullingCircle() const { return mCullingCircle; }

protected:

	/* Protected initialization method */
	virtual void init(vector<_float> const * pVertices, vector<_float> const * pTextureCoordinates) = 0;

	/* Calculate circle and center for culling */
	void calculateCullingCircle(vector<_float> const * pVertices);

	/* Members */
	_uint mVertexCount;
	CullingCircle mCullingCircle;
};

#endif
