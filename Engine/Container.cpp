#include "Container.h"

#include "Engine/External/gl_core_3_3.h"
#include <GLFW/glfw3.h>

void Container::start(System system, std::string title, _uint resolutionX, _uint resolutionY)
{
	/* Fill members */
	mSystem = system;
	mTitle = title;
	mResolutionX = resolutionX;
	mResolutionY = resolutionY;

	/* Initialize members */
	mSceneManager.init(this);
	if (mSystem == System::Linux_OGL33 || mSystem == System::Windows_OGL33)
	{
		mspRenderInterface = shared_ptr<RenderInterface>(new RenderInterface_OGL33);
	}
	mspRenderInterface->init();
	mAssetManager.init(getRenderInterface());
	mRenderManager.init(getRenderInterface());

	/* At the moment, GLFW only */
	mLastTime = static_cast<_float>(glfwGetTime());

	/* Initialize the library */
    if (!glfwInit())
	{
		// return -1;
    }

    /* Tell GLFW to set core profile */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */;
	window = glfwCreateWindow(mResolutionX, mResolutionY, mTitle.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
    }

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

    /* Initialize OpenGL */
    ogl_LoadFunctions();

	/* Initialization of rendering */
	mspRenderInterface->setupInterface();

	/* Initialization method filled by user */
    init();

	/* Run it */
    run();
}

void Container::run()
{
	while (!glfwWindowShouldClose(window))
	{
		/* Update delta time */
		updateDeltaTime();

		/* Update method filled by user */
		update();

		/* Scene graph update */
		mSceneManager.updateSceneGraph();

		/* Recalculate world transformations and draw */
		draw();
	}

	glfwTerminate();
}

void Container::draw()
{
	/* Clear old color buffer */
	mspRenderInterface->clearColorBuffer();

	/* Actual drawing including recalculation of world transfomation */
	mRenderManager.draw();

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
}

_float Container::getAspectRatio() const
{
	return ((_float)mResolutionX) / mResolutionY;
}

void Container::updateDeltaTime()
{
	_float currentTime = static_cast<_float>(glfwGetTime());
	mDeltaTime = currentTime - mLastTime;
	mLastTime = currentTime;
}
