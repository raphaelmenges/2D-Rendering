#include "RenderLayer.h"

void RenderLayer::init(RenderManager const * pRenderManager, RenderInterface const * pRenderInterface)
{
	mpRenderManager = pRenderManager;
	mpRenderInterface = pRenderInterface;
}

void RenderLayer::registerOpaqueItem(Mesh const * pMesh, Material const * pMaterial, RenderParameter * pRenderParameter)
{
	registerItemInRenderMap(mOpaqueRenderMap, pMesh, pMaterial, pRenderParameter);
}

_uint RenderLayer::createTransparentBucket(
	Mesh const * pMesh,
	Material const * pMaterial,
	_float const * pLocalMedianZ)
{
	/* Create render item */
	shared_ptr<RenderItem> spRenderItem = mpRenderInterface->createRenderItem(pMesh, pMaterial, pLocalMedianZ);

	/* Save it to queue and map */
	_uint bucketHandle = mTransparentBucketCounter;
	mTransparentQueue.push_back(RenderBucket(bucketHandle, spRenderItem));
	mTransparentMap[bucketHandle] = spRenderItem;

	/* Increment counter */
	mTransparentBucketCounter++;

	/* Return handle of bucket */
	return bucketHandle;
}

void RenderLayer::registerTransparentItem(_uint bucketHandle, RenderParameter * pRenderParameter)
{
	mTransparentMap.at(bucketHandle)->registerParameter(pRenderParameter);
}

void RenderLayer::registerAdditiveItem(Mesh const * pMesh, Material const * pMaterial, RenderParameter * pRenderParameter)
{
	registerItemInRenderMap(mAdditiveRenderMap, pMesh, pMaterial, pRenderParameter);
}

void RenderLayer::unregisterOpaqueItem(
	Mesh const * pMesh,
	Material const * pMaterial,
	RenderParameter * pRenderParameter)
{
	unregisterItemInRenderMap(mOpaqueRenderMap, pMesh, pMaterial, pRenderParameter);
}

void RenderLayer::deleteTransparentBucket(_uint bucketHandle)
{
	/* Delete bucket */
	mTransparentMap.erase(bucketHandle);

	/* Delete it also from queue */
	_int index = -1;
	for (int i = 0; i < mTransparentQueue.size(); i++)
	{
		if (mTransparentQueue[i].bucketHandle == bucketHandle)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		mTransparentQueue.erase(mTransparentQueue.begin() + index);
	}
}


void RenderLayer::unregisterTransparentItem(_uint bucketHandle, RenderParameter * pRenderParameter)
{
	/* Unregister parameter set for this bucket */
	mTransparentMap.at(bucketHandle)->unregisterParameter(pRenderParameter);

	/* Decided not to delete empty buckets! */
	/*if(mTransparentMap.at(bucketHandle)->registeredParametersCount() <= 0)
	{
		deleteTransparentBucket(bucketHandle);
	}*/
}

void RenderLayer::unregisterAdditiveItem(
	Mesh const * pMesh,
	Material const * pMaterial,
	RenderParameter * pRenderParameter)
{
	unregisterItemInRenderMap(mAdditiveRenderMap, pMesh, pMaterial, pRenderParameter);
}

void RenderLayer::draw()
{
	/* Clear depth buffer */
	mpRenderInterface->clearDepthBuffer();

	/* OPAQUE */
	drawRenderMap(mOpaqueRenderMap);

	/* TRANSPARENT */
	mpRenderInterface->changeFromOpaqueToTransparentRendering();

	/* Sorting */
	sort(mTransparentQueue.begin(), mTransparentQueue.end(), RenderBucketComparator());

	/* Drawing */
	for (RenderBucket bucket : mTransparentQueue)
	{
		bucket.spRenderItem->getMaterial()->bind();
		bucket.spRenderItem->bind();
		bucket.spRenderItem->draw();
	}

	/* ADDITIVE */
	mpRenderInterface->changeFromTransparentToAdditiveRendering();

	/* Drawing */
	drawRenderMap(mAdditiveRenderMap);

	mpRenderInterface->changeFromAdditiveToOpaqueRendering();
}

void RenderLayer::registerItemInRenderMap(
	RenderMap& rRenderMap,
	Mesh const * pMesh,
	Material const * pMaterial,
	RenderParameter * pRenderParameter)
{
	/* Check, wether material is known */
	if (rRenderMap.find(pMaterial) != rRenderMap.end())
	{
		if (rRenderMap[pMaterial].find(pMesh) != rRenderMap[pMaterial].end())
		{
			rRenderMap[pMaterial][pMesh]->registerParameter(pRenderParameter);
		}
		else
		{
			/* Mesh is not known for this material, so introduce it */
			shared_ptr<RenderItem> spRenderItem = mpRenderInterface->createRenderItem(pMesh, pMaterial);
			spRenderItem->registerParameter(pRenderParameter);
			rRenderMap[pMaterial][pMesh] = spRenderItem;
		}
	}
	else
	{
		/* Material is not known, so introduce it */
		shared_ptr<RenderItem> spRenderItem = mpRenderInterface->createRenderItem(pMesh, pMaterial);
		spRenderItem->registerParameter(pRenderParameter);
		map<Mesh const *, shared_ptr<RenderItem> > renderItems;
		renderItems[pMesh] = spRenderItem;
		rRenderMap.insert(make_pair(pMaterial, renderItems));
	}
}

void RenderLayer::unregisterItemInRenderMap(
	RenderMap& rRenderMap,
	Mesh const * pMesh,
	Material const * pMaterial,
	RenderParameter * pRenderParameter)
{
	/* Unregister parameter in render item */
	shared_ptr<RenderItem> spRenderItem = rRenderMap[pMaterial][pMesh];
	spRenderItem->unregisterParameter(pRenderParameter);

	/* Check, whether render item is still in use */
	if (spRenderItem->registeredParametersCount() <= 0)
	{
		/* No? Then erase it from mesh */
		rRenderMap[pMaterial].erase(pMesh);

		/* Check, whether material is needed by a mesh anymore */
		if (rRenderMap[pMaterial].size() <= 0)
		{
			rRenderMap.erase(pMaterial);
		}
	}
}

void RenderLayer::drawRenderMap(const RenderMap& rRenderMap)
{
	/* Go over materials */
	for (pair<Material const *, map<Mesh const *, shared_ptr<RenderItem> > > material_mesh_item : rRenderMap)
	{
		/* Bind material */
		material_mesh_item.first->bind();

		Logger::debug("Bind material!");

		for (pair<Mesh const *, shared_ptr<RenderItem> > mesh_item : material_mesh_item.second)
		{
			Logger::debug("Bind render item!");

			/* Bind render item */
			mesh_item.second->bind();

			/* Draw render item */
			mesh_item.second->draw();
		}
	}
}
