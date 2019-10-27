#ifndef MESH_RENDERER_H_
#define MESH_RENDERER_H_

#include "ObjectComponent.h"
#include "../../../Rendering/Material.h"
#include "../../../Rendering/Mesh.h"
#include "../../../Rendering/RenderParameter.h"
#include "../../../Structs/CullingCircle.h"

enum class RenderType
{
    Opaque, Transparent, Additive
};


class MeshRenderer : public ObjectComponent
{
public:

    /* Constructors */
    MeshRenderer() {}

    /* Destructor */
    virtual ~MeshRenderer() {}

    /* Initialization */
    virtual void init(
        Object* pObject,
        _uint renderLayerHandle,
        const Material &material,
        RenderType renderType);

    /* Getter */
    RenderParameter* getRenderParameter() { return &mRenderParameter; }
    const CullingCircle& getMeshCullingCircle() const { return mpMesh->getCullingCircle(); }

protected:

    /* Members */
    RenderParameter mRenderParameter;
    _uint mRenderLayerHandle;
    Mesh const * mpMesh;
    Material const * mpMaterial;
};

#endif
