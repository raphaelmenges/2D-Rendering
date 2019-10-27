#include "SceneManager.h"
#include "Container.h"

void SceneManager::init(Container const * pContainer)
{
	mpContainer = pContainer;
	mRoot.init("Root", mpContainer);
	mRoot.setRooted(true);
}

void SceneManager::updateSceneGraph()
{
	mRoot.updateTransformation();
	mRoot.updateCullingFromRoot();
}

void SceneManager::attachScene(Scene* pScene)
{
	mScenes.insert(pScene);
	mRoot.attachChild(pScene->getRoot());
}

void SceneManager::detachScene(Scene* pScene)
{
	mScenes.erase(pScene);
	mRoot.detachChild(pScene->getRoot());
}

void SceneManager::detachAllScenes()
{
	mScenes.clear();
}
