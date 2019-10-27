#ifndef SCENE_H_
#define SCENE_H_

#include "Global.h"
#include "Nodes/Camera.h"

class Scene
{
public:

    /* Friends */
    friend class SceneManager;

    /* Constructor */
    Scene() {}

    /* Destructor */
    virtual ~Scene() {}

    /* Initialization */
    void init(Container const * pContainer)
    {
        mpContainer = pContainer;
        mSceneRoot.init("Scene", mpContainer);
        mSceneRoot.setScene(this);
    }

    /* Getter */
    Camera const * const * getCameraPointer() const {return &mpCamera;}
	Camera const * getCamera() const { return mpCamera; }

    /* Setter */
    void linkCamera(Camera const * pCamera) {mpCamera = pCamera;}

    /* Node operations */
    void attachNode(Node* pNode) {mSceneRoot.attachChild(pNode);}
    void detachNode(Node* pNode) {mSceneRoot.detachChild(pNode);}
    void detachAllNodes() {mSceneRoot.detachAllChildren();}

private:

    /* Get scene root node */
    Node* getRoot() {return &mSceneRoot;}

    /* Members */
    Camera const * mpCamera;
    Node mSceneRoot;
    Container const * mpContainer;
};

#endif
