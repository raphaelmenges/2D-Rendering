#include "RenderInterface.h"

RenderInterface::RenderInterface()
{

}

RenderInterface::~RenderInterface()
{

}

shared_ptr<Mesh> RenderInterface::createMesh(string path) const
{
	shared_ptr<Mesh> spMesh = instantiateMesh();
	spMesh->init(path);
	return spMesh;
}

shared_ptr<Mesh> RenderInterface::createMesh(PrimitiveMesh primitiveMesh) const
{
	shared_ptr<Mesh> spMesh = instantiateMesh();
	spMesh->init(primitiveMesh);
	return spMesh;
}
