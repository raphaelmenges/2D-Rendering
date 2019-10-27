#include "MeshRenderer.h"
#include "../Object.h"

void MeshRenderer::init(
    Object* pObject,
    _uint renderLayerHandle,
    const Material &material,
    RenderType renderType)
{
    ObjectComponent::init(pObject);

    /* Save render layer handle */
    mRenderLayerHandle = renderLayerHandle;

    /* Mesh */
    mpMesh = mpObject->getAssetManager()->loadMesh(PrimitiveMesh::Quad);

    /* Material */
    mpMaterial = &material;

    /* Render parameter */
    mRenderParameter.init(mpMaterial, mpObject->isVisible());
    mRenderParameter.linkModelMatrix(mpObject->getModelMatrix());

    if (renderType == RenderType::Opaque)
    {
        mpObject->getRenderManager()->getRenderLayer(mRenderLayerHandle)->registerOpaqueItem(mpMesh, mpMaterial, &mRenderParameter);
    }
    else if (renderType == RenderType::Transparent)
    {
        _uint bucketHandle = mpObject->getRenderManager()->getRenderLayer(mRenderLayerHandle)->createTransparentBucket(mpMesh, mpMaterial);
        mpObject->getRenderManager()->getRenderLayer(mRenderLayerHandle)->registerTransparentItem(bucketHandle, &mRenderParameter);
    }
    else
    {
        mpObject->getRenderManager()->getRenderLayer(mRenderLayerHandle)->registerAdditiveItem(mpMesh, mpMaterial, &mRenderParameter);
    }
}
