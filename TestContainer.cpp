#include "TestContainer.h"

void TestContainer::init()
{
	Logger::info("Init");

	/* Render Layers */
	renderLayerAHandle = this->getRenderManager()->addRenderLayer();
	renderLayerBHandle = this->getRenderManager()->addRenderLayer();

	/* Cameras */
	cameraA.init("Camera", screenOrientation, this, this->getAspectRatio(), Vector2f(4, 4), -1, 1);
	cameraB.init("Camera", screenOrientation, this, this->getAspectRatio(), Vector2f(4, 4), -1, 1);

	/* Scene */

	sceneA.init(this);
	this->attachScene(&sceneA);
	//sceneB.init(&camera, this);
	//this->attachScene(&sceneB);
	sceneA.linkCamera(&cameraA);

	standardMaterialA.init(this->getAssetManager());
	standardMaterialA.setDiffuse("Grass.png");

	standardMaterialB.init(this->getAssetManager());
	standardMaterialB.setDiffuse("Transparent.png", false, true);

	standardMaterialC.init(this->getAssetManager(), StandardMaterialType::Masked);
	standardMaterialC.setDiffuse("Alphatest.png", true, true);

	/* Images */
	imageA.init("ImageA", this, this->getAssetManager(), this->getRenderManager(), renderLayerAHandle, standardMaterialA, RenderType::Opaque);
	imageB.init("ImageB", this, this->getAssetManager(), this->getRenderManager(), renderLayerAHandle, standardMaterialB, RenderType::Transparent);
	imageC.init("ImageC", this, this->getAssetManager(), this->getRenderManager(), renderLayerAHandle, standardMaterialA, RenderType::Opaque);
	imageD.init("ImageD", this, this->getAssetManager(), this->getRenderManager(), renderLayerAHandle, standardMaterialC, RenderType::Additive);
	imageE.init("ImageE", this, this->getAssetManager(), this->getRenderManager(), renderLayerAHandle, standardMaterialC, RenderType::Additive);

	/* Camera attachen */
	sceneA.attachNode(&cameraA);
	sceneA.attachNode(&cameraB);

	imageB.setLocalZ(0.5f);

	sceneA.attachNode(&imageA);

	imageA.setScale(2);

	imageA.attachChild(&imageC);
	imageC.move(Vector2f(0, 4));

	sceneA.attachNode(&imageB);

	// Log asset manager
	Logger::debug("### AssetManager ###");
	Logger::debug("MeshCount: ", to_string(this->getAssetManager()->getMeshCount()));
	Logger::debug("PrimitiveMeshCount: ", to_string(this->getAssetManager()->getPrimitiveMeshCount()));
	Logger::debug("ShaderCount: ", to_string(this->getAssetManager()->getShaderCount()));
	Logger::debug("TextureCount: ", to_string(this->getAssetManager()->getTextureCount()));

	// Log render manager
	Logger::debug("### RenderManager ###");
	Logger::debug("ActiveRenderItemCount: ", to_string(this->getRenderManager()->getRenderLayer(renderLayerAHandle)->getOpaqueRenderMapItemCount()));

	// Test
	this->getRenderManager()->moveRenderLayerToBack(renderLayerAHandle);
}

void TestContainer::update()
{
	Logger::debug("New Update!");

	sceneA.linkCamera(&cameraB);
	cameraB.rotate(mDeltaTime);

	//imageA.rotate(mDeltaTime * 20);

	testTime += static_cast<_double>(mDeltaTime);

	//imageA.setLocalPosition(Vector2f(10 * static_cast<_float>(sin(testTime)), 0));
	imageB.setLocalPosition(Vector2f(10 * static_cast<_float>(-sin(testTime)), 0));
}

int main()
{
	TestContainer container;
	container.start(System::Linux_OGL33, "HelloGame", 720, 480);
}
