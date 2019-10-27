#include "AssetManager.h"

#include "Rendering/StandardMaterial.h"

void AssetManager::init(RenderInterface const * pRenderInterface)
{
	mpRenderInterface = pRenderInterface;
}

Mesh const * AssetManager::loadMesh(string path)
{
	/* Find mesh in set via path */
	if (mMeshes[path] != _null)
	{
		return mMeshes[path].get();
	}
	else
	{
		/* Was not found, so add it */
		shared_ptr<Mesh> spMesh = mpRenderInterface->createMesh(path);
		mMeshes[path] = spMesh;
		return spMesh.get();
	}
}

Mesh const * AssetManager::loadMesh(PrimitiveMesh primitiveMesh)
{
	/* Find mesh in set via path */
	if (mPrimitiveMeshes[primitiveMesh] != _null)
	{
		return mPrimitiveMeshes[primitiveMesh].get();
	}
	else
	{
		/* Was not found, so add it */
		shared_ptr<Mesh> spMesh = mpRenderInterface->createMesh(primitiveMesh);
		mPrimitiveMeshes[primitiveMesh] = spMesh;
		return spMesh.get();
	}
}

Texture const * AssetManager::loadTexture(string path, TextureType type, TextureWrap wrap, TextureFiltering filtering)
{
	/* Find texture in set via path */
	if (mTextures[path] != _null)
	{
		return mTextures[path].get();
	}
	else
	{
		/* Was not found, so add it */
		shared_ptr<Texture> spTexture = mpRenderInterface->createTexture(path, type, wrap, filtering);
		mTextures[path] = spTexture;
		return spTexture.get();
	}
}

Shader const * AssetManager::loadShader(ShaderType shaderType)
{
	/* Find shader in set via path */
	if (mShaders[shaderType] != _null)
	{
		return mShaders[shaderType].get();
	}
	else
	{
		/* Was not found, so add it */
		shared_ptr<Shader> spShader = mpRenderInterface->createShader(shaderType);
		mShaders[shaderType] = spShader;
		return spShader.get();
	}
}
