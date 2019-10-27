#ifndef OBJECT_COMPONENT_H_
#define OBJECT_COMPONENT_H_

#include "../../NodeComponents/NodeComponent.h"

/* Forward declaration */
class Object;

class ObjectComponent
{
public:

    /* Constructors */
    ObjectComponent();

    /* Destructor */
    virtual ~ObjectComponent() {}

    /* Initialization */
    virtual void init(Object* pObject);

protected:

    /* Members */
    NodeComponent mNodeComponent;
    Object* mpObject;
};

#endif
