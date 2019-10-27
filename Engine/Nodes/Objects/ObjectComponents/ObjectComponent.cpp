#include "ObjectComponent.h"
#include "../Object.h"

ObjectComponent::ObjectComponent()
{
    mpObject = _null;
}

void ObjectComponent::init(Object* pObject)
{
    mNodeComponent.init(static_cast<Node*>(pObject));
    mpObject = pObject;
}
