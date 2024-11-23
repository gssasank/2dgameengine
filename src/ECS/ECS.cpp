#include "ECS.h"
#include <vector>

int Entity::GetId() const{
    return id;
}

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    //TODO: Write this function.
}

std::vector<Entity> System::GetSystemEntities() const { // const added because they only return values and they do not modify anything.
    return System::entities;
}

const Signature& System::GetComponentSignature() const { // const added because they only return values and they do not modify anything.
    return System::componentSignature;
}
