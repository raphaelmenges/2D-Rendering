#include "Node.h"
#include "../Container.h"

Node::Node()
{
	mLocalZ = 0;
	mLocalRotation = 0;
	mWorldTransformationMatrix = Matrix4f::eye();
	mpParent = _null;
	mWasNeverAttached = true;
	mRooted = false;
	mpScene = _null;
}

void Node::init(std::string name, Container const * pContainer)
{
	mName = name;
	mpContainer = pContainer;

	/* Update world transformation next time */
	worldTransformationNeedsUpdate();
}

Node const * Node::getParent() const
{
	return mpParent;
}

Vector2f Node::getLocalPosition() const
{
	return mLocalPosition;
}

_float Node::getLocalZ() const
{
	return mLocalZ;
}

_float Node::getLocalRotation() const
{
	return mLocalRotation;
}

Matrix4f const * Node::getWorldTransformationMatrix() const
{
	return &mWorldTransformationMatrix;
}

_float const * Node::getLocalZPointer() const
{
	return &mLocalZ;
}

void Node::setLocalPosition(Vector2f localPosition)
{
	mLocalPosition = localPosition;

	/* Update world transformation next time */
	worldTransformationNeedsUpdate();
}

void Node::setLocalRotation(_float localRotation)
{
	mLocalRotation = localRotation;

	/* Update world transformation next time */
	worldTransformationNeedsUpdate();
}

void Node::setLocalZ(_float localZ)
{
	mLocalZ = localZ;

	/* Update world transformation next time */
	worldTransformationNeedsUpdate();
}

void Node::move(Vector2f offset)
{
	mLocalPosition += offset;

	/* Update world transformation next time */
	worldTransformationNeedsUpdate();
}

void Node::rotate(_float rotation)
{
	mLocalRotation += rotation;

	/* Update world transformation next time */
	worldTransformationNeedsUpdate();
}

void Node::setParent(Node* pParent)
{
	/* Check for existing parent */
	if (hasParent())
	{
		mpParent->detachChild(this);
	}

	/* Set new parent */
	mpParent = pParent;

	/* Tell parent about it */
	bool rooted;
	if (hasParent())
	{
		mpParent->attachChild(this);
		rooted = mpParent->isRooted();

		/* Update world transformation next time */
		worldTransformationNeedsUpdate();
	}
	else
	{
		/* No new parent */
		rooted = false;
	}

	/* Rooted */
	if (mWasNeverAttached || rooted != mRooted)
	{
		setRooted(rooted);
	}

	/* Parent was set, so remember about it */
	mWasNeverAttached = false;
}

void Node::attachChild(Node* pChild)
{
	mChildren.insert(pChild);

	/* Culling circle of this and parents need update */
	cullingCircleNeedsUpdate();

	/* Set scene only if there is one */
	if (hasScene())
	{
		pChild->setScene(mpScene);
	}

	/* Set this as parent if necessary */
	if (pChild->getParent() != this)
	{
		pChild->setParent(this);
	}
}

void Node::detachChild(Node* pChild)
{
	/* First, check whether node is in set */
	if (mChildren.find(pChild) != mChildren.end())
	{
		mChildren.erase(pChild);
		pChild->setParent(_null);

		cullingCircleNeedsUpdate();
	}
}

void Node::detachAllChildren()
{
	for (Node* pChild : mChildren)
	{
		detachChild(pChild);
	}
}

void Node::updateTransformation()
{
	/* Before drawing, update own transformation and childrens' */
	updateWorldTransformationIfNecessary();

	/* Update all children */
	for (Node* pChild : mChildren)
	{
		pChild->updateTransformation();
	}
}

void Node::updateCullingFromRoot()
{
	/* Just forward it to all scene roots, because root has no scene */
	for (Node* pChild : mChildren)
	{
		pChild->updateCulling();
	}
}

void Node::worldTransformationNeedsUpdate()
{
	mWorldTransformationNeedsUpdate = true;
}

void Node::cullingCircleNeedsUpdate()
{
	mCullingCircleNeedsUpdate = true;

	/* Parents need update too */
	if (hasParent())
	{
		mpParent->cullingCircleNeedsUpdate();
	}
}

void Node::updateWorldTransformationIfNecessary()
{
	/* Only update if bool was set */
	if (mWorldTransformationNeedsUpdate)
	{
		updateWorldTransformation();
		mWorldTransformationNeedsUpdate = false;
	}
}

void Node::updateWorldTransformation()
{
	/* Rotation */
	Matrix4f rotationMatrix = Matrix4f::rotationZAxis(mLocalRotation);

	/* Position */
	Matrix4f translationMatrix = Matrix4f::eye();
	translationMatrix.setField(0, 3, mLocalPosition.x());
	translationMatrix.setField(1, 3, mLocalPosition.y());
	translationMatrix.setField(2, 3, mLocalZ);

	/* Do own update */
	mWorldTransformationMatrix = translationMatrix * rotationMatrix;

	/* Use transformation of parent if available */
	if (hasParent())
	{
		mWorldTransformationMatrix = *(mpParent->getWorldTransformationMatrix()) * mWorldTransformationMatrix;
	}

	/* Children must do the same */
	for (Node* pChild : mChildren)
	{
		/* Tell children, that they have to update world transform before next update */
		pChild->worldTransformationNeedsUpdate();
	}

	/* Update culling circle next time */
	cullingCircleNeedsUpdate();
}

void Node::updateCulling()
{
	/* Do it only when there is a scene set (camera needed) */
	if (hasScene() && isRooted())
	{
		/* Update culling circle */
		updateCullingCircleIfNecessary();

		/* Only continue, when this or some child or grandchild is cullable */
		if (mSomethingCullableInGraph)
		{
			/* Then, decide visibilty */
			bool culled = !circleIntersection(
				mCullingCircle,
				mpScene->getCamera()->getViewCircle());

			/* Set culling */
			bool wasCulled = isCulled();
			if (wasCulled != culled)
			{
				setCulled(culled);
			}

			/* If not culled, let's let the children check */
			if (!culled)
			{
				for (Node* pChild : mChildren)
				{
					pChild->updateCulling();
				}
			}
		}
	}
}

void Node::updateCullingCircleIfNecessary()
{
	/* Only update if bool was set */
	if (mCullingCircleNeedsUpdate)
	{
		/* Update this */
		mSomethingCullableInGraph = updateCullingCircle();

		mCullingCircleNeedsUpdate = false;
	}
}

bool Node::updateCullingCircle()
{
	/* Vector for cullable children */
	vector<Node const *> cullableChildren;

	if (!mChildren.empty())
	{
		/* First, calculate center of all circles */
		Vector2f center = 0;
		for (Node* pChild : mChildren)
		{
			/* Updat culling circle of children */
			if (pChild->updateCullingCircle())
			{
				center += pChild->getCullingCircle().center;
				cullableChildren.push_back(pChild);
			}
		}

		/* Only continue if there were cullable children */
		if (!cullableChildren.empty())
		{
			center /= static_cast<_float>(cullableChildren.size());

			/* Get most far center plus radius */
			_float radius = 0;
			for (Node const * pChild : cullableChildren)
			{
				CullingCircle childCullingCircle = pChild->getCullingCircle();
				Vector2f vector = childCullingCircle.center - center;
				_float radiusCandidate = vector.length() + childCullingCircle.radius;
				if (radiusCandidate > radius)
				{
					radius = radiusCandidate;
				}
			}

			/* Save results to members */
			mCullingCircle.center = center;
			mCullingCircle.radius = radius;

			/* Something cullable was found */
			return true;
		}
	}

	/* No cullable children */
	mCullingCircle.center = this->getLocalPosition();
	mCullingCircle.radius = 0;
	return false;
}

bool Node::circleIntersection(
	const CullingCircle& rOne,
	const CullingCircle& rOther) const
{
	return (rOne.center - rOther.center).length() <= (rOne.radius + rOther.radius);
}

void Node::mergeCullingCircles(
	CullingCircle& rMerged,
	const CullingCircle& rOne,
	const CullingCircle& rOther) const
{
	// TODO: One could find better center and so smaller radius (more math...)
	rMerged.center = (rOne.center + rOther.center) / 2;
	rMerged.radius = ((rOne.center - rOther.center).length()) / 2 + max(rOne.radius, rOther.radius);
}

void Node::setRooted(bool rooted)
{
	mRooted = rooted;

	/* Update all children */
	for (Node* pChild : mChildren)
	{
		pChild->setRooted(mRooted);
	}
}

bool Node::isRooted() const
{
	return mRooted;
}

void Node::setScene(Scene const * pScene)
{
	if (mpScene != pScene)
	{
		mpScene = pScene;

		/* Update all children */
		for (Node* pChild : mChildren)
		{
			pChild->setScene(mpScene);
		}
	}
}

void Node::setCulled(bool culled)
{
	mCulled = culled;

	/* Update all children */
	for (Node* pChild : mChildren)
	{
		pChild->setCulled(culled);
	}
}
