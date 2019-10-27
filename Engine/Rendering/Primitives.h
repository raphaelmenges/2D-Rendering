#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include "../Global.h"
#include <vector>

namespace Primitive
{

	/* Quad from -0.5 to 0.5 */
	const vector<_float> quadVertices = {
        -0.5,-0.5,0, 0.5,-0.5,0, 0.5,0.5,0,
        0.5,0.5,0, -0.5,0.5,0, -0.5,-0.5,0
	};

	const vector<_float> quadTextureCoordinates = {
        0,0, 1,0, 1,1,
        1,1, 0,1, 0,0
	};
}

#endif
