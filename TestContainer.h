#ifndef TEST_CONTAINER_H_
#define TEST_CONTAINER_H_

#include "Engine/Container.h"
#include "Engine/Rendering/StandardMaterial.h"

class TestContainer : public Container
{
public:

	/* Constructor */
	TestContainer() {}

	/* Destructor */
	virtual ~TestContainer() {}

	/* Initialization */
	virtual void init();

	/* Update */
	virtual void update();

private:
	StandardMaterial standardMaterialA;
	StandardMaterial standardMaterialB;
	StandardMaterial standardMaterialC;

	Image imageA;
	Image imageB;
	Image imageC;
	Image imageD;
	Image imageE;
	Image imageF;

	Camera cameraA;
	Camera cameraB;
	Scene sceneA;
	Scene sceneB;

	_double testTime = 0;
	_uint renderLayerAHandle;
	_uint renderLayerBHandle;


};

#endif
