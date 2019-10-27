#include "Image.h"
#include "../../Container.h"

void Image::init(
	std::string name,
	Container const * pContainer,
	AssetManager* pAssetManager,
	RenderManager* pRenderManager,
	_uint renderLayerHandle,
	const Material &material,
	RenderType renderType)
{
    Object::init(name, pContainer, pAssetManager, pRenderManager);
    mMeshRenderer.init(this, renderLayerHandle, material, renderType);
}

void Image::setScene(Scene const * pScene)
{
	Node::setScene(pScene);
    mMeshRenderer.getRenderParameter()->linkCameraPointer(mpScene->getCameraPointer());
}

CullingCircle Image::getOwnCullingCircle() const
{
    CullingCircle meshCircle = mMeshRenderer.getMeshCullingCircle();
	CullingCircle circle;

	/* Get center of mesh and move it by world transformation matrix */
	circle.center.setX(mWorldTransformationMatrix.getField(0, 3) + meshCircle.center.x());
	circle.center.setY(mWorldTransformationMatrix.getField(1, 3) + meshCircle.center.y());

	/* Get radius of mesh and use scale */
	circle.radius = meshCircle.radius  * this->getScale().max();

	/* Return own culling circle */
	return circle;
}

void Image::updateRenderingVisibility()
{
    mMeshRenderer.getRenderParameter()->setVisibility(isVisible());
}
