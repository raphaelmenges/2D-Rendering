#ifndef RENDER_INTERFACE_OGL33_H_
#define RENDER_INTERFACE_OGL33_H_

#include "../RenderInterface.h"

#include <memory>

/* OpenGL 3.3 */
#include "Mesh_OGL33.h"
#include "Texture_OGL33.h"
#include "Shader_OGL33.h"
#include "RenderItem_OGL33.h"

class RenderInterface_OGL33 : public RenderInterface
{
public:

	/* Constructor */
	RenderInterface_OGL33();

	/* Destructor */
	virtual ~RenderInterface_OGL33();

	/* Initialization */
	virtual void init();

	/* Texture */
	virtual shared_ptr<Texture> createTexture(string path, TextureType type, TextureWrap wrap, TextureFiltering filtering) const;

	/* Shader */
	virtual shared_ptr<Shader> createShader(ShaderType shaderType) const;

	/* RenderItem */
	virtual shared_ptr<RenderItem> createRenderItem(Mesh const * pMesh, Material const * pMaterial, _float const * pLocalMedianZ = _null) const;

	/* Rendering setup */
	virtual void setupInterface() const;

	/* Transition from opaque to transparent rendering */
	virtual void changeFromOpaqueToTransparentRendering() const;

	/* Transition from transparent to additive rendering */
	virtual void changeFromTransparentToAdditiveRendering() const;

	/* Transition from additive to opaque rendering */
	virtual void changeFromAdditiveToOpaqueRendering() const;

	/* Clear screen */
	virtual void clearScreen() const;

	/* Clear color buffer */
	virtual void clearColorBuffer() const;

	/* Clear depth buffer */
	virtual void clearDepthBuffer() const;

protected:

	/* Internal mesh instantiation method */
	virtual shared_ptr<Mesh> instantiateMesh() const;

};

#endif
