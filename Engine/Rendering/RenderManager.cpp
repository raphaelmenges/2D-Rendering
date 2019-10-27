#include "RenderManager.h"

void RenderManager::init(RenderInterface const * pRenderInterface)
{
	mpRenderInterface = pRenderInterface;
	mLayerCounter = 0;
}

void RenderManager::draw()
{
	for (shared_ptr<RenderLayer> spLayer : mLayerQueue)
	{
		spLayer->draw();
	}
}

_uint RenderManager::addRenderLayer()
{
	shared_ptr<RenderLayer> layer(new RenderLayer);
	layer->init(this, mpRenderInterface);

	/* Add to queue */
	mLayerQueue.push_back(layer);

	/* Add to map */
	_uint layerHandle = mLayerCounter;
	mLayerMap[layerHandle] = layer;

	/* Increment layer counter */
	mLayerCounter++;

	/* Return handle */
	return layerHandle;
}

void RenderManager::moveRenderLayerInFrontOf(_uint layerHandle, _uint otherLayerHandle)
{
	vector<shared_ptr<RenderLayer> > newLayerQueue;

	/* Get layers from map */
	shared_ptr<RenderLayer> spOneLayer = mLayerMap[layerHandle];
	shared_ptr<RenderLayer> spOtherLayer = mLayerMap[otherLayerHandle];

	/* Copy layers */
	for (shared_ptr<RenderLayer> spLayer : mLayerQueue)
	{
		if (spLayer != spOneLayer && spLayer != spOtherLayer)
		{
			newLayerQueue.push_back(spLayer);
		}
		else if (spLayer == spOtherLayer)
		{
			newLayerQueue.push_back(spOtherLayer);
			newLayerQueue.push_back(spOneLayer);
		}
	}

	mLayerQueue = newLayerQueue;
}

void RenderManager::moveRenderLayerBehind(_uint layerHandle, _uint otherLayerHandle)
{
	vector<shared_ptr<RenderLayer> > newLayerQueue;

	/* Get layers from map */
	shared_ptr<RenderLayer> spOneLayer = mLayerMap[layerHandle];
	shared_ptr<RenderLayer> spOtherLayer = mLayerMap[otherLayerHandle];

	/* Copy layers */
	for (shared_ptr<RenderLayer> spLayer : mLayerQueue)
	{
		if (spLayer != spOneLayer && spLayer != spOtherLayer)
		{
			newLayerQueue.push_back(spLayer);
		}
		else if (spLayer == spOtherLayer)
		{
			newLayerQueue.push_back(spOneLayer);
			newLayerQueue.push_back(spOtherLayer);
		}
	}

	mLayerQueue = newLayerQueue;
}

void RenderManager::moveRenderLayerToFront(_uint layerHandle)
{
	vector<shared_ptr<RenderLayer> > newLayerQueue;

	/* Get layer from map */
	shared_ptr<RenderLayer> spOneLayer = mLayerMap[layerHandle];

	/* Copy layers */
	for (shared_ptr<RenderLayer> spLayer : mLayerQueue)
	{
		if (spLayer != spOneLayer)
		{
			newLayerQueue.push_back(spLayer);
		}
	}
	newLayerQueue.push_back(spOneLayer);

	mLayerQueue = newLayerQueue;
}

void RenderManager::moveRenderLayerToBack(_uint layerHandle)
{
	vector<shared_ptr<RenderLayer> > newLayerQueue;

	/* Get layer from map */
	shared_ptr<RenderLayer> spOneLayer = mLayerMap[layerHandle];

	/* Copy layers */
	newLayerQueue.push_back(spOneLayer);
	for (shared_ptr<RenderLayer> spLayer : mLayerQueue)
	{
		if (spLayer != spOneLayer)
		{
			newLayerQueue.push_back(spLayer);
		}
	}

	mLayerQueue = newLayerQueue;
}