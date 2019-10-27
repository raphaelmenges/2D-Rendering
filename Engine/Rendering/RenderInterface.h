#ifndef RENDER_INTERFACE_H_
#define RENDER_INTERFACE_H_

#include "../Global.h"

#include <memory>

/* OpenGL 3.3 */
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "RenderItem.h"

class RenderInterface
{
public:

	/* Constructor */
	RenderInterface();

	/* Destructor */
	virtual ~RenderInterface();

	/* Initialization */
	virtual void init() = 0;

	/* Mesh */
	shared_ptr<Mesh> createMesh(string path) const;
	shared_ptr<Mesh> createMesh(PrimitiveMesh primitiveMesh) const;

	/* Texture */
	virtual shared_ptr<Texture> createTexture(string path, TextureType type, TextureWrap wrap, TextureFiltering filtering) const = 0;

	/* Shader */
	virtual shared_ptr<Shader> createShader(ShaderType shaderType) const = 0;

	/* RenderItem */
	virtual shared_ptr<RenderItem> createRenderItem(Mesh const * pMesh, Material const * pMaterial, _float const * pLocalMedianZ = _null) const = 0;

	/* Rendering setup */
	virtual void setupInterface() const = 0;

	/* Transition from opaque to transparent rendering */
	virtual void changeFromOpaqueToTransparentRendering() const = 0;

	/* Transition from transparent to additive rendering */
	virtual void changeFromTransparentToAdditiveRendering() const = 0;

	/* Transition from additive to opaque rendering */
	virtual void changeFromAdditiveToOpaqueRendering() const = 0;

	/* Clear screen */
	virtual void clearScreen() const = 0;

	/* Clear color buffer */
	virtual void clearColorBuffer() const = 0;

	/* Clear depth buffer */
	virtual void clearDepthBuffer() const = 0;

protected:

	/* Internal mesh instantiation method */
	virtual shared_ptr<Mesh> instantiateMesh() const = 0;

};

#endif
