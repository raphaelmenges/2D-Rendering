#ifndef RENDER_MANAGER_H_
#define RENDER_MANAGER_H_

#include <vector>
#include <map>
#include <memory>

#include "RenderLayer.h"

class RenderManager
{
public:

	/* Constructor */
	RenderManager() {}

	/* Destructor */
	virtual ~RenderManager() {}

	/* Initialization */
	void init(RenderInterface const * pRenderInterface);

	/* Getter of layer*/
	RenderLayer* getRenderLayer(_uint layerHandle) { return mLayerMap[layerHandle].get(); }

	/* Drawing */
	void draw();

	/* Add render layer */
	_uint addRenderLayer();

	/* Move layer before other */
	void moveRenderLayerInFrontOf(_uint layerHandle, _uint otherLayerHandle);

	/* Move layer behind other */
	void moveRenderLayerBehind(_uint layerHandle, _uint otherLayerHandle);

	/* Move layer to front */
	void moveRenderLayerToFront(_uint layerHandle);

	/* Move layer to back */
	void moveRenderLayerToBack(_uint layerHandle);

private:

	_uint mLayerCounter;
	RenderInterface const * mpRenderInterface;

	/* Front of vector is back in rendering */
	vector<shared_ptr<RenderLayer> > mLayerQueue;

	map<_uint, shared_ptr<RenderLayer> > mLayerMap;

};

#endif
