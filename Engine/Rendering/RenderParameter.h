#ifndef RENDER_PARAMETER_H_
#define RENDER_PARAMETER_H_

#include "../Global.h"
#include "../Math/Math.h"
#include "../Nodes/Camera.h"
#include "Material.h"
#include <map>
#include <utility>

const string RENDER_PARAMETER_PROJECTION_VIEW_MATRIX = "projectionViewMatrix";
const string RENDER_PARAMETER_MODEL_MATRIX = "modelMatrix";

const Matrix4f INITIAL_MATRIX_4F = Matrix4f::eye();
const ColorRGBA INITIAL_COLOR_RGBA = ColorRGBA(1,1,1,1);

/* Forward declaration */
class RenderItem;

class RenderParameter
{
public:

	/* Constructor */
	RenderParameter()
	{
		mpOwner = _null;
		mVisible = false;
	}

	/* Destructor */
	virtual ~RenderParameter() {}

	/* Initialization */
    void init(Material const * Material, bool visible);

	/* Get parameter */
    const map<string, Matrix4f>& getMatrices4f() const { return mMatrices4f; }
    Matrix4f * getMatrix4f(string name) { return &(mMatrices4f.at(name)); }
    const map<string, ColorRGBA>& getColorsRGBAs() const { return mColorRGBAs; }
    ColorRGBA * getColorRGBA(string name) { return &(mColorRGBAs.at(name)); }

	/* Owner */
	void setOwner(RenderItem * pOwner) { mpOwner = pOwner; }
	RenderItem * getOwner() { return mpOwner; }

	/* Camera */
	void linkCameraPointer(Camera const * const * ppCamera) { mppCamera = ppCamera; }
	Camera const * getCamera() const { return *mppCamera; }

	/* Model matrix */
	void linkModelMatrix(Matrix4f const * pModelMatrix) { mpModelMatrix = pModelMatrix; }
	Matrix4f const * getModelMatrix() const { return mpModelMatrix; }

	/* Visibilty */
	void setVisibility(bool visible);
	bool isVisible() const;

private:

    /* Add parameters */
    void addMatrix4f(string name);
    void addColorRGBA(string name);

	/* Members */
	RenderItem * mpOwner;
	bool mVisible;
    map<string, Matrix4f> mMatrices4f;
    map<string, ColorRGBA> mColorRGBAs;
	Camera const * const * mppCamera;
	Matrix4f const * mpModelMatrix;

};

#endif
