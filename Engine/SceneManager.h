#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "Nodes/Node.h"
#include "Scene.h"
#include "Global.h"

#include <set>

class Container;

class SceneManager
{
public:

    /* Constructor */
    SceneManager() {}

    /* Destructor */
    virtual ~SceneManager() {}

    /* Initialization */
    void init(Container const * pContainer);

    /* Updating */
    void updateSceneGraph();

    /* Scene handling */
    void attachScene(Scene* pScene);
    void detachScene(Scene* pScene);
    void detachAllScenes();

private:

    /* Members */
    set<Scene*> mScenes;
    Node mRoot;
    Container const * mpContainer;
};

#endif
