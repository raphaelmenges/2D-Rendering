#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

void Mesh::init(string path)
{
	/* Generate full path */
	string fullpath = ASSETS_PATH + path;

	/* Import using tinyobj */
	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;

	string error = tinyobj::LoadObj(shapes, materials, fullpath.c_str());

	if (error.length() > 0)
	{
		Logger::error(error);
	}

	/* Extract vertices and texture coordinates */
	vector<_float> vertices;
	vector<_float> textureCoordinates;

	/* Iterate over shapes (only one should be there...) */
	for (tinyobj::shape_t shape : shapes)
	{
		/* Iterate over indices and collect vertices and texture coordinates */
		for (_int index : shape.mesh.indices)
		{
			_int vertexIndex = index * 3;
			vertices.push_back(shape.mesh.positions[vertexIndex]);
			vertices.push_back(shape.mesh.positions[vertexIndex+1]);
			vertices.push_back(shape.mesh.positions[vertexIndex+2]);

			_int textureCoordinateIndex = index * 2;
			textureCoordinates.push_back(shape.mesh.texcoords[textureCoordinateIndex]);
			textureCoordinates.push_back(shape.mesh.texcoords[textureCoordinateIndex+1]);
		}
	}

	/* It is ok here to use pointers to local scope variables */
	init(&vertices, &textureCoordinates);
}

void Mesh::init(PrimitiveMesh primitiveMesh)
{
	switch (primitiveMesh)
	{
	case PrimitiveMesh::Quad:
		init(&(Primitive::quadVertices), &(Primitive::quadTextureCoordinates));
		break;
	}

	calculateCullingCircle(&(Primitive::quadVertices));
}

void Mesh::calculateCullingCircle(vector<_float> const * pVertices)
{
	/* Iterate through vertices and find maximum values */
	_float x, y;
	_float minX = 10000000;
	_float minY = 10000000;
	_float maxX = -10000000;
	_float maxY = -10000000;

	for (_uint i = 0; i < mVertexCount; i++)
	{
		/* X */
		x = pVertices->at(i * 3);
		if (x > maxX) { maxX = x; }
		if (x < minX) { minX = x; }

		/* Y */
		y = pVertices->at(i * 3 + 1);
		if (y > maxY) { maxY = y; }
		if (y < minY) { minY = y; }
	}

	/* Calculate width and height */
	_float width = maxX - minX;
	_float height = maxY - minY;
	_float centerX = (minX + maxX) / 2;
	_float centerY = (minY + maxY) / 2;

	/* Calculate center and radius of circle */
	mCullingCircle.center.setXY(centerX, centerY);
	mCullingCircle.radius = sqrt(width * width + height * height) / 2;
}
