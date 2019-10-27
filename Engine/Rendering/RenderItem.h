#ifndef RENDER_ITEM_H_
#define RENDER_ITEM_H_

#include "../Global.h"
#include "Mesh.h"
#include "Material.h"
#include "../Math/Math.h"
#include "RenderParameter.h"
#include <set>
#include <utility>
#include <memory>

class RenderManager;

class RenderItem
{
public:

	/* Friend */
	friend class RenderParameter;

	/* Constructor */
	RenderItem();

	/* Destructor */
	virtual ~RenderItem();

	/* Initialization */
	virtual void init(Mesh const * pMesh, Material const * pMaterial, _float const * pLocalMedianZ = _null);

	/* Activate for parameters */
	void registerParameter(RenderParameter * pRenderParameter);

	/* Deactivate for parameters */
	void unregisterParameter(RenderParameter * pRenderParameter);

	/* Bind before drawing */
	virtual void bind() const = 0;

	/* Draw it with all parameters */
	void draw() const;

	/* Calculate median z value */
	_float medianZ() const;

	/* Getter for material and mesh */
	Material const * getMaterial() const { return mpMaterial; }
	Mesh const * getMesh() const { return mpMesh; }

	/* Getter for parameter count */
	_uint registeredParametersCount() const { return static_cast<_uint>(activeParametersCount() + inactiveParametersCount()); }
	_uint activeParametersCount() const { return static_cast<_uint>(mActiveParameters.size()); }
	_uint inactiveParametersCount() const { return static_cast<_uint>(mInactiveParameters.size()); }

protected:

	/* Draw with one parameterset */
	virtual void drawOneInstance(RenderParameter const * pRenderParameter) const = 0;

	/* Activate for parameter (called by parameter) */
	void activateParameter(RenderParameter const * pRenderParameter);

	/* Deactivate for parameter (called by parameter) */
	void deactivateParameter(RenderParameter const * pRenderParameter);

	/* Update shader input locations cache (called by parameter) */
	virtual void updateShaderInputLocationsCache(RenderParameter const * pRenderParameter) = 0;

	/* Members */
	Mesh const * mpMesh = _null;
	Material const * mpMaterial = _null;
	_float const * mpLocalMedianZ = _null;

	set<RenderParameter const *> mActiveParameters;
	set<RenderParameter const *> mInactiveParameters;
};

#endif
