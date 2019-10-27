#include "RenderItem.h"
#include "RenderManager.h"

RenderItem::RenderItem()
{
}

RenderItem::~RenderItem()
{
}

void RenderItem::init(Mesh const * pMesh, Material const * pMaterial, _float const * pLocalMedianZ)
{
	mpMesh = pMesh;
	mpMaterial = pMaterial;
	mpLocalMedianZ = pLocalMedianZ;
}

void RenderItem::registerParameter(RenderParameter * pRenderParameter)
{
	/* Decide, to which set it should be added */
	if (pRenderParameter->isVisible())
	{
		mActiveParameters.insert(pRenderParameter);
	}
	else
	{
		mInactiveParameters.insert(pRenderParameter);
	}

	/* Set owner in parameter */
	pRenderParameter->setOwner(this);

	/* Update shader input locations cache */
	updateShaderInputLocationsCache(pRenderParameter);
}

void RenderItem::unregisterParameter(RenderParameter * pRenderParameter)
{
	/* Decide, to which set it should be erased */
	if (pRenderParameter->isVisible())
	{
		mActiveParameters.erase(pRenderParameter);
	}
	else
	{
		mInactiveParameters.erase(pRenderParameter);
	}

	/* Set owner in parameter */
	pRenderParameter->setOwner(_null);
}

void RenderItem::draw() const
{
	/* Draw it with all active parameters */
	for (RenderParameter const * pParameter : mActiveParameters)
	{
		drawOneInstance(pParameter);
	}
}

_float RenderItem::medianZ() const
{
	if (mpLocalMedianZ != _null)
	{
		return *mpLocalMedianZ;
	}
	else
	{
		/* Calculate median z value of all parameters */
		_float medianZ = 0;
		for (RenderParameter const * pParameter : mActiveParameters)
		{
			medianZ += pParameter->getModelMatrix()->getField(2, 3);
		}
		for (RenderParameter const * pParameter : mInactiveParameters)
		{
			medianZ += pParameter->getModelMatrix()->getField(2, 3);
		}
		return (medianZ / registeredParametersCount());
	}
}

void RenderItem::activateParameter(RenderParameter const * pRenderParameter)
{
	mInactiveParameters.erase(pRenderParameter);
	mActiveParameters.insert(pRenderParameter);
}

void RenderItem::deactivateParameter(RenderParameter const * pRenderParameter)
{
	mActiveParameters.erase(pRenderParameter);
	mInactiveParameters.insert(pRenderParameter);
}
