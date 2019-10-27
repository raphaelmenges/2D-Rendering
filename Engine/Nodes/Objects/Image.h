#ifndef IMAGE_H_
#define IMAGE_H_

#include "Object.h"

// Test
#include <iostream>
#include <memory>

#include "../../Rendering/RenderManager.h"
#include "ObjectComponents/MeshRenderer.h"

class Image : public Object
{
public:

	/* Constructors */
	Image() {}

	/* Destructor */
	virtual ~Image() {}

	/* Initialization */
	virtual void init(
		string name,
		Container const * pContainer,
		AssetManager* pAssetManager,
		RenderManager* pRenderManager,
		_uint renderLayerHandle,
		const Material &material,
		RenderType renderType);

protected:

	/* Get own culling circle */
	virtual CullingCircle getOwnCullingCircle() const;

    /* Set the scene */
	virtual void setScene(Scene const * pScene);

    /* Update rendering */
    virtual void updateRenderingVisibility();

    /* Members */
    MeshRenderer mMeshRenderer;
};

#endif
