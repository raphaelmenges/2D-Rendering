#ifndef ASSET_MANAGER_H_
#define ASSET_MANAGER_H_

#include <memory>
#include <map>

#include "Global.h"
#include "Rendering/RenderInterface.h"
#include "Rendering/Mesh.h"
#include "Rendering/Material.h"
#include "Rendering/Shader.h"

class AssetManager
{
public:

	/* Constructor */
	AssetManager() {}

	/* Destructor */
	virtual ~AssetManager() {}

	/* Initialization */
	void init(RenderInterface const * pRenderInterface);

	/* Load mesh. Path in content folder. */
	Mesh const * loadMesh(string path);

	/* Load primitive mesh */
	Mesh const * loadMesh(PrimitiveMesh primitiveMesh);

	/* Load texture */
	Texture const * loadTexture(string path, TextureType type, TextureWrap wrap, TextureFiltering filtering);

	/* Load shader. Path in content folder. */
	Shader const * loadShader(ShaderType shaderType);

	/* Getter */
	_uint getMeshCount() const { return static_cast<_uint>(mMeshes.size()); }
	_uint getPrimitiveMeshCount() const { return static_cast<_uint>(mPrimitiveMeshes.size()); }
	_uint getTextureCount() const { return static_cast<_uint>(mTextures.size()); }
	_uint getShaderCount() const { return static_cast<_uint>(mShaders.size()); }

private:

	/* Members */
	RenderInterface const * mpRenderInterface;

	/* Meshes */
	map<string, shared_ptr<Mesh> > mMeshes;
	map<PrimitiveMesh, shared_ptr<Mesh> > mPrimitiveMeshes;

	/* Textures */
	map<string, shared_ptr<Texture> > mTextures;

	/* Shaders */
	map<ShaderType, shared_ptr<Shader> > mShaders;
};

#endif
