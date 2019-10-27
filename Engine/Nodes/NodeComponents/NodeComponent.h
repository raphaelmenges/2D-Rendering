#ifndef NODE_COMPONENT_H_
#define NODE_COMPONENT_H_

#include "../../Global.h"

/* Forward declaration */
class Node;

class NodeComponent
{
public:

    /* Constructors */
    NodeComponent();

    /* Destructor */
    virtual ~NodeComponent() {}

    /* Initialization */
    virtual void init(Node* pNode);

protected:

    /* Members */
    Node* mpNode;
};

#endif
