#include "ECS.h"
#include <vector>
#include <algorithm>

int Entity::GetId() const{
    return id;
}

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    //TODO: Write this function.

    auto lambda = [&entity](Entity otherEntity){
        return entity.GetId() == otherEntity.GetId();
    };

    entities.erase(std::remove_if(entities.begin(), entities.end(), lambda),entities.end());
}

std::vector<Entity> System::GetSystemEntities() const { // const added because they only return values, and they do not modify anything.
    return System::entities;
}

const Signature& System::GetComponentSignature() const { // const added because they only return values, and they do not modify anything.
    return System::componentSignature;
}
