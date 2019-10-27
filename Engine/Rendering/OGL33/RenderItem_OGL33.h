#ifndef RENDER_ITEM_OGL33_H_
#define RENDER_ITEM_OGL33_H_

#include "../RenderItem.h"

#include "Mesh_OGL33.h"
#include "Shader_OGL33.h"
#include <map>

class RenderItem_OGL33 : public RenderItem
{
public:

	/* Constructor */
	RenderItem_OGL33();

	/* Destructor */
	virtual ~RenderItem_OGL33();

	/* Initialization */
	virtual void init(Mesh const * pMesh, Material const * pMaterial, _float const * pLocalMedianZ = _null);

	/* Bind before drawing */
	virtual void bind() const;

protected:

	/* Draw with one parameterset */
	virtual void drawOneInstance(RenderParameter const * pRenderParameter) const;

	/* Update shader input locations cache (called by parameter) */
	virtual void updateShaderInputLocationsCache(RenderParameter const * pRenderParameter);

	/* Members */
	Mesh_OGL33 const * mpMesh_OGL33;
	Shader_OGL33 const * mpShader_OGL33;
	_uint mVertexArrayObject;
	map<string, _int> mUniformLocationsCache;
	_int mCameraUniformLocation;
	_int mWorldPositionUniformLocation;
};

#endif
