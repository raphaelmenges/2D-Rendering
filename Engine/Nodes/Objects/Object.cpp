#include "Object.h"

Object::Object()
{
	mScale = 1;
	mHidden = false;
}

void Object::init(std::string name, Container const * pContainer, AssetManager* pAssetManager, RenderManager* pRenderManager)
{
	Node::init(name, pContainer);
	mpAssetManager = pAssetManager;
	mpRenderManager = pRenderManager;
}

void Object::hide()
{
	mHidden = true;
	updateRenderingVisibility();
}

void Object::show()
{
	mHidden = false;
	updateRenderingVisibility();
}

bool Object::isVisible() const
{
    return !(mHidden || !mRooted || mCulled);
}

void Object::updateWorldTransformation()
{
	Node::updateWorldTransformation();
	updateModelMatrix();
}

bool Object::updateCullingCircle()
{
	/* Replace Node's method */
	if (Node::updateCullingCircle())
	{
		/* There are renderable nodes */
		CullingCircle ownCircle = getOwnCullingCircle();

		/* Merge both circles */
		Node::mergeCullingCircles(mCullingCircle, ownCircle, mCullingCircle);
	}
	else
	{
		/* No relevant children, then do it alone */
		mCullingCircle = getOwnCullingCircle();
	}

	/* This is object, though this is cullable */
	return true;
}

void Object::updateModelMatrix()
{
	Matrix4f scaleMatrix = Matrix4f::eye();
	scaleMatrix.setField(0, 0, mScale.x());
	scaleMatrix.setField(1, 1, mScale.y());
	mModelMatrix = mWorldTransformationMatrix * scaleMatrix;
}

void Object::setRooted(bool rooted)
{
	Node::setRooted(rooted);
	updateRenderingVisibility();
}

void Object::setCulled(bool culled)
{
	Node::setCulled(culled);
	updateRenderingVisibility();
}
