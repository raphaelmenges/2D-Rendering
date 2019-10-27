#include "Camera.h"
#include "../Container.h"

void Camera::init(std::string name, ScreenOrientation screenOrientation, Container const * pContainer, _float aspectRatio, Vector2f minFrustumScale, _float nearPlane, _float farPlane)
{
	Node::init(name, pContainer);

	mAspectRatio = aspectRatio;
	mMinFrustumScale = minFrustumScale;
	mNearPlane = nearPlane;
	mFarPlane = farPlane;
	mScreenOrientation = screenOrientation;

	updateOrientationMatrix();
	updateProjectionMatrix();
}

void Camera::setMinFrustumScale(Vector2f minFrustumScale)
{
	mMinFrustumScale = minFrustumScale;
	updateProjectionMatrix();
}

void Camera::setAspectRatio(_float aspectRatio)
{
	mAspectRatio = aspectRatio;
	updateProjectionMatrix();
}

void Camera::setScreenOrientation(ScreenOrientation screenOrientation)
{
	mScreenOrientation = screenOrientation;
	updateOrientationMatrix();
}

void Camera::updateOrientationMatrix()
{
	_float orientation;
	switch (mScreenOrientation)
	{
	case ScreenOrientation::Degree0:
		orientation = 0;
		break;
	case ScreenOrientation::Degree90:
		orientation = 90;
		break;
	case ScreenOrientation::Degree180:
		orientation = 180;
		break;
	case ScreenOrientation::Degree270:
		orientation = 270;
		break;
	}
	mOrientationMatrix = Matrix4f::rotationZAxis(orientation);

	/* Calculate full projection view matrix */
	mProjectionViewMatrix = mProjectionMatrix * mOrientationMatrix * mViewMatrix;
}

void Camera::updateProjectionMatrix()
{
	_float minFrustumAspectRatio = mMinFrustumScale.x() / mMinFrustumScale.y();

	const _float two = 2;

	/* Compare aspect ratios*/
	if (mAspectRatio <= minFrustumAspectRatio)
	{
		/* Window higher than expected */
		mLeft = -mMinFrustumScale.x() / two;
		mRight = -mLeft;

		/* Calculate necessary values */
		mBottom = -minFrustumAspectRatio / mAspectRatio * mMinFrustumScale.y() / two;
		mTop = -mBottom;

	}
	else
	{
		/* Window wider than expected */
		mBottom = -mMinFrustumScale.y() / two;
		mTop = -mBottom;

		/* Calculate necessary values */
		mLeft = -mAspectRatio / minFrustumAspectRatio * mMinFrustumScale.x() / two;
		mRight = -mLeft;
	}

	mProjectionMatrix = Matrix4f::orthographic(mLeft, mRight, mBottom, mTop, mNearPlane, mFarPlane);

	/* Calculate full projection view matrix */
	mProjectionViewMatrix = mProjectionMatrix * mOrientationMatrix * mViewMatrix;

	/* Update of view circle necessary */
	updateViewCircle();

	/* Members */
	mFrustumWidth = mRight - mLeft;
	mFrustumHeight = mTop - mBottom;
}

void Camera::updateWorldTransformation()
{
	Node::updateWorldTransformation();

	/* View Matrix */
	Matrix4f rotationMatrix = Matrix4f(mWorldTransformationMatrix.getField(0, 0), mWorldTransformationMatrix.getField(1, 0),
		mWorldTransformationMatrix.getField(2, 0), 0,

		mWorldTransformationMatrix.getField(0, 1), mWorldTransformationMatrix.getField(1, 1),
		mWorldTransformationMatrix.getField(2, 1), 0,

		mWorldTransformationMatrix.getField(0, 2), mWorldTransformationMatrix.getField(1, 2),
		mWorldTransformationMatrix.getField(2, 2), 0,

		0, 0, 0, 1);

	Matrix4f translationMatrix = Matrix4f::eye();
	translationMatrix.setField(0, 3, -mWorldTransformationMatrix.getField(0, 3));
	translationMatrix.setField(1, 3, -mWorldTransformationMatrix.getField(1, 3));

	mViewMatrix = rotationMatrix * translationMatrix;

	/* Calculate full projection view matrix */
	mProjectionViewMatrix = mProjectionMatrix * mOrientationMatrix * mViewMatrix;

	/* Update of view circle necessary */
	updateViewCircle();
}

void Camera::updateViewCircle()
{
	mViewCircle.center.setX(mWorldTransformationMatrix.getField(0, 3));
	mViewCircle.center.setY(mWorldTransformationMatrix.getField(1, 3));

	/* Choose longest distance to corner (view circle center is always at center...) */
	mViewCircle.radius = sqrt(mLeft * mLeft + mTop * mTop);
}
