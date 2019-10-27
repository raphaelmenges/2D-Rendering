#ifndef RENDER_LAYER_H_
#define RENDER_LAYER_H_

#include <set>
#include <map>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>

#include "../Global.h"
#include "RenderItem.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "RenderInterface.h"

/* Forward declaration */
class RenderManager;

/* Typedefs for better readability */
typedef map<Material const *, map<Mesh const *, shared_ptr<RenderItem> > > RenderMap;

/* Bucket for transparent items */
struct RenderBucket
{
	_uint bucketHandle;
	shared_ptr<RenderItem> spRenderItem;

	RenderBucket(_uint bucketHandle, shared_ptr<RenderItem> spRenderItem)
	{
		this->bucketHandle = bucketHandle;
		this->spRenderItem = spRenderItem;
	}
};

/* Comparator for transparent buckets */
struct RenderBucketComparator
{
	inline bool operator() (const RenderBucket& bucket1, const RenderBucket& bucket2)
	{
		return bucket1.spRenderItem->medianZ() < bucket2.spRenderItem->medianZ();
	}
};

class RenderLayer
{
public:

	/* Constructor */
	RenderLayer()
	{
		mTransparentBucketCounter = 0;
	}

	/* Destructor */
	virtual ~RenderLayer() {}

	/* Initialization */
	void init(RenderManager const * pRenderManager, RenderInterface const * pRenderInterface);

	/* Register opaque render item */
	void registerOpaqueItem(
		Mesh const * pMesh,
		Material const * pMaterial,
		RenderParameter * pRenderParameter);

	/* Create bucket for transparent items. Returns handle of bucket */
	_uint createTransparentBucket(
		Mesh const * pMesh,
		Material const * pMaterial,
		_float const * pLocalMedianZ = _null);

	/* Register transparent item */
	void registerTransparentItem(_uint bucketHandle, RenderParameter * pRenderParameter);

	/* Register additive item */
	void registerAdditiveItem(
		Mesh const * pMesh,
		Material const * pMaterial,
		RenderParameter * pRenderParameter);

	/* Unregister opaque item */
	void unregisterOpaqueItem(
		Mesh const * pMesh,
		Material const * pMaterial,
		RenderParameter * pRenderParameter);

	/* Delete whole bucket of transparent items */
	void deleteTransparentBucket(_uint bucketHandle);

	/* Unregister transparent item */
	void unregisterTransparentItem(_uint bucketHandle, RenderParameter * pRenderParameter);

	/* Unregister additive item */
	void unregisterAdditiveItem(
		Mesh const * pMesh,
		Material const * pMaterial,
		RenderParameter * pRenderParameter);

	/* Drawing */
	void draw();

	/* Getter */
	_uint getOpaqueRenderMapItemCount() const { return static_cast<_uint>(mOpaqueRenderMap.size()); }

private:

	/* Insert item into render map (all but transparent items) */
	void registerItemInRenderMap(
		RenderMap& rRenderMap,
		Mesh const * pMesh,
		Material const * pMaterial,
		RenderParameter * pRenderParameter);

	/* Erase item from render map (all but transparent items) */
	void unregisterItemInRenderMap(
		RenderMap& rRenderMap,
		Mesh const * pMesh,
		Material const * pMaterial,
		RenderParameter * pRenderParameter);

	/* Draw render map */
	void drawRenderMap(const RenderMap& rRenderMap);

	/* Members */
	RenderManager const * mpRenderManager;
	RenderInterface const * mpRenderInterface;

	/* Render map for opaque items */
	RenderMap mOpaqueRenderMap;

	/* Render queue for transparent stuff, easy to sort */
	vector<RenderBucket> mTransparentQueue;

	/* Same items as in queue but easier index based access */
	map<_uint, shared_ptr<RenderItem> > mTransparentMap;

	/* Counter for transparent buckets */
	_uint mTransparentBucketCounter;

	/* Render map for additive items */
	RenderMap mAdditiveRenderMap;
};

#endif
