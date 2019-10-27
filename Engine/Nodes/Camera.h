#ifndef CAMERA_H_
#define CAMERA_H_

#include "Node.h"
#include "../Types.h"
#include "../Math/Math.h"

/* Responsible for View- and Projection-Matrix */

enum class ScreenOrientation;

class Camera : public Node
{
public:

	/* Constructor */ // minFrustumScale is the real scale, not the half
	Camera() {}

	/* Destructor */
	virtual ~Camera() {}

	/* Init */
	virtual void init(std::string name, ScreenOrientation screenOrientation, Container const * pContainer, _float aspectRatio, Vector2f minFrustumScale, _float near, _float far);

	/* Getter */
	Matrix4f const * getViewMatrix() const { return &mViewMatrix; }
	Matrix4f const * getProjectionMatrix() const { return &mProjectionMatrix; }
	Matrix4f const * getProjectionViewMatrix() const { return &mProjectionViewMatrix; }
	const CullingCircle& getViewCircle() const { return mViewCircle; }

	/* Setter */
	void setMinFrustumScale(Vector2f minFrustumScale);
	void setAspectRatio(_float aspectRatio);
	void setScreenOrientation(ScreenOrientation screenOrientation);

protected:

	/* Update */
	void updateOrientationMatrix();
	void updateProjectionMatrix();
	virtual void updateWorldTransformation();
	void updateViewCircle();

	/* Members */
	Vector2f mMinFrustumScale;
	_float mNearPlane;
	_float mFarPlane;
	_float mAspectRatio;
	Matrix4f mOrientationMatrix;
	Matrix4f mViewMatrix;
	Matrix4f mProjectionMatrix;
	Matrix4f mProjectionViewMatrix;
	ScreenOrientation mScreenOrientation;

	_float mLeft, mRight, mBottom, mTop;
	_float mFrustumWidth, mFrustumHeight;

	CullingCircle mViewCircle;
};

#endif
