#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Math/Math.h"
#include "Global.h"
#include "Nodes/Node.h"
#include "Nodes/Camera.h"
#include "Nodes/Objects/Image.h"
#include "SceneManager.h"
#include "Rendering/RenderManager.h"
#include "AssetManager.h"
#include "Rendering/OGL33/RenderInterface_OGL33.h"
#include "Scene.h"

#include <memory>

enum class System
{
	Linux_OGL33, Windows_OGL33
};

enum class ScreenOrientation
{
	Degree0, Degree90, Degree180, Degree270
};

class Container
{
public:

	/* Constructor */
	Container() {}

	/* Destructor */
	virtual ~Container() {}

	/* Start, used by user! */
	virtual void start(System system, std::string title, _uint resolutionX, _uint resolutionY) final;

	/* Initialization, filled by user! */
	virtual void init() = 0;

	/* Running */
	virtual void run() final;

	/* Update, filled by user! */
	virtual void update() = 0;

	/* Draw everything */
	virtual void draw() final;

	/* Getter */
	_float getAspectRatio() const;
	_float getDeltaTime() const { return mDeltaTime; }

	/* Scenes */
	void attachScene(Scene* pScene) { mSceneManager.attachScene(pScene); }
	void detachScene(Scene* pScene) { mSceneManager.detachScene(pScene); }
	void detachAllScenes() { mSceneManager.detachAllScenes(); }

	RenderInterface* getRenderInterface() { return mspRenderInterface.get(); }
	AssetManager* getAssetManager() { return &mAssetManager; }
	RenderManager* getRenderManager() { return &mRenderManager; }

protected:

	/* Test */
	ScreenOrientation screenOrientation = ScreenOrientation::Degree0;

	/* Members */
	System mSystem;
	std::string mTitle;
	_uint mResolutionX;
	_uint mResolutionY;

	/* For delta time calculation */
	_float mLastTime;
	_float mDeltaTime;

	// GLFW only for now
	GLFWwindow* window;

private:

	/* Calculate delta time */
	void updateDeltaTime();

	SceneManager mSceneManager;
	shared_ptr<RenderInterface> mspRenderInterface;
	AssetManager mAssetManager;
	RenderManager mRenderManager;
};

#endif
