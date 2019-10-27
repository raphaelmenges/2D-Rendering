#include "RenderInterface_OGL33.h"

RenderInterface_OGL33::RenderInterface_OGL33()
{

}

RenderInterface_OGL33::~RenderInterface_OGL33()
{

}

void RenderInterface_OGL33::init()
{
	// nothing to do here
}

shared_ptr<Texture> RenderInterface_OGL33::createTexture(string path, TextureType type, TextureWrap wrap, TextureFiltering filtering) const
{
	shared_ptr<Texture> spTexture = shared_ptr<Texture_OGL33>(new Texture_OGL33);
	spTexture->init(path, type, wrap, filtering);
	return spTexture;
}

shared_ptr<Shader> RenderInterface_OGL33::createShader(ShaderType shaderType) const
{
	shared_ptr<Shader> spShader = shared_ptr<Shader_OGL33>(new Shader_OGL33);
	spShader->init(shaderType);
	return spShader;
}

shared_ptr<RenderItem> RenderInterface_OGL33::createRenderItem(Mesh const * pMesh, Material const * pMaterial, _float const * pLocalMedianZ) const
{
	shared_ptr<RenderItem> spRenderItem = shared_ptr<RenderItem_OGL33>(new RenderItem_OGL33);
	spRenderItem->init(pMesh, pMaterial, pLocalMedianZ);
	return spRenderItem;
}

void RenderInterface_OGL33::setupInterface() const
{
	/* Textures */
	glEnable(GL_TEXTURE_2D);

	/* Depth */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void RenderInterface_OGL33::changeFromOpaqueToTransparentRendering() const
{
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderInterface_OGL33::changeFromTransparentToAdditiveRendering() const
{
	glBlendFunc(GL_ONE, GL_ONE);
}

void RenderInterface_OGL33::changeFromAdditiveToOpaqueRendering() const
{
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

shared_ptr<Mesh> RenderInterface_OGL33::instantiateMesh() const
{
	return shared_ptr<Mesh>(new Mesh_OGL33);
}

void RenderInterface_OGL33::clearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderInterface_OGL33::clearColorBuffer() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderInterface_OGL33::clearDepthBuffer() const
{
	glClear(GL_DEPTH_BUFFER_BIT);
}
