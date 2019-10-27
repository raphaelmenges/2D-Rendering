#ifndef OBJECT_H_
#define OBJECT_H_

#include "../Node.h"
#include "../../AssetManager.h"
#include "../../Rendering/RenderManager.h"
#include "ObjectComponents/ObjectComponent.h"

class Object : public Node
{
public:

	/* Constructors */
	Object();

	/* Destructor */
	virtual ~Object() {}

	/* Initialization */
    virtual void init(std::string name, Container const * pContainer, AssetManager* pAssetManager, RenderManager* pRenderManager);

	/* Getter */
	Vector2f getScale() const { return mScale; }
    Matrix4f const * getModelMatrix() const { return &mModelMatrix;}
    AssetManager* getAssetManager() { return mpAssetManager; }
    RenderManager* getRenderManager() { return mpRenderManager; }

	/* Setter */
	void setScale(Vector2f scale) { mScale = scale; updateModelMatrix(); }
	void setScale(_float scale) { mScale = Vector2f(scale); updateModelMatrix(); }

	/* Visibility */
	void hide();
	void show();

    /* Check own visibilty */
    bool isVisible() const;

protected:

	/* Add updating model matrix */
	virtual void updateWorldTransformation();

	/* Use mesh culling circle */
	virtual bool updateCullingCircle();

	/* Update model matrix */
	void updateModelMatrix();

	/* Rooted */
	void virtual setRooted(bool rooted);

	/* Culling */
	void virtual setCulled(bool culled);

	/* Update rendering */
    virtual void updateRenderingVisibility() = 0;

	/* Get own culling circle */
	virtual CullingCircle getOwnCullingCircle() const = 0;

	/** Members **/
	AssetManager* mpAssetManager;
	RenderManager* mpRenderManager;

	bool mHidden;

	Vector2f mScale;
	Matrix4f mModelMatrix;
};

#endif
