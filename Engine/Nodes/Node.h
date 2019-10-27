#ifndef NODE_H_
#define NODE_H_

#include "../Types.h"
#include "../Math/Math.h"
#include "../Structs/CullingCircle.h"
#include "NodeComponents/NodeComponent.h"
#include <set>

/* Forward declaration */
class Container;
class Scene;

class Node
{
public:

	/* Friend, who may draw */
	friend class SceneManager;

	/* Friend, who may set scene */
	friend class Scene;

	/* Constructors */
	Node();

	/* Destructor */
	virtual ~Node() {}

	/* Initialization */
	virtual void init(string name, Container const * pContainer);

	/* Getter */
	Node const * getParent() const;
	Vector2f getLocalPosition() const;
	_float getLocalZ() const;
	_float getLocalRotation() const;
	Matrix4f const * getWorldTransformationMatrix() const;
	_float const * getLocalZPointer() const;
	CullingCircle getCullingCircle() const { return mCullingCircle; }

	/* Setter */
	void virtual setLocalPosition(Vector2f localPosition);
	void virtual setLocalRotation(_float localRotation);
	void virtual setLocalZ(_float localZ);

	/* Update */
	void virtual move(Vector2f offset);
	void virtual rotate(_float rotation);

	/* Node stuff */
	void setParent(Node* pParent);
	void attachChild(Node* pChild);
	void detachChild(Node* pChild);
	void detachAllChildren();
	std::set<Node*> getChildren() { return mChildren; }

protected:

	/* Updating by manager or recursive */
	void updateTransformation();
	void updateCullingFromRoot();

	/* Set need for update */
	void worldTransformationNeedsUpdate();
	void cullingCircleNeedsUpdate();

	/* Update world transformation */
	void updateWorldTransformationIfNecessary();
	virtual void updateWorldTransformation();

	/* Update culling */
	void updateCulling();

	/* Update culling circle */
	void updateCullingCircleIfNecessary();

	/* Update culling circle. Returns whether there are cullables anywhere */
	virtual bool updateCullingCircle();

	/* Calculate circle intersection */
	bool circleIntersection(
		const CullingCircle& rOne,
		const CullingCircle& rOther) const;

	/* Merge two culling circles */
	void mergeCullingCircles(
		CullingCircle& rMerged,
		const CullingCircle& rOne,
		const CullingCircle& rOther) const;

	/* Rooted */
	void virtual setRooted(bool rooted);
	bool isRooted() const;

	/* Scene */
	virtual void setScene(Scene const * pScene);
	bool hasScene() const { return mpScene != _null; }

	/* Parenting */
	bool hasParent() const { return mpParent != _null; }

	/* Culling */
	void virtual setCulled(bool culled);
	bool isCulled() const { return mCulled; }

	/** Members **/
	std::string mName;

	bool mRooted;
	bool mCulled;
	bool mWasNeverAttached;
	bool mSomethingCullableInGraph;

	Container const * mpContainer;
	Scene const * mpScene;
	Node* mpParent;
	std::set<Node*> mChildren;

	Vector2f mLocalPosition;
	_float mLocalZ;
	_float mLocalRotation;
	Matrix4f mWorldTransformationMatrix;

	bool mWorldTransformationNeedsUpdate;
	bool mCullingCircleNeedsUpdate;

	CullingCircle mCullingCircle;
};

#endif
