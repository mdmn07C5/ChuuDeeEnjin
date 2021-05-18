#include "ECS/ECS.h"

void Entity::AddGroup(Group group)

{
    groupBitSet[group] = true;
    manager.AddToGroup(this, group);
}