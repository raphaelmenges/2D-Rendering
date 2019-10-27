#ifndef CULLING_CIRCLE_H_
#define CULLING_CIRCLE_H_

#include "../Math/Math.h"

struct CullingCircle
{
	CullingCircle()
	{
		/* Standard constructor of Vector2f is alread 0,0 */
		radius = 0;
	}

	CullingCircle(Vector2f center, _float radius)
	{
		this->center = center;
		this->radius = radius;
	}

	Vector2f center;
	_float radius;
};

#endif
