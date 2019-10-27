#include "NodeComponent.h"
#include "../Node.h"

NodeComponent::NodeComponent()
{
    mpNode = _null;
}

void NodeComponent::init(Node* pNode)
{
    mpNode = pNode;
}
