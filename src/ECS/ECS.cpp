#include "ECS.h"
#include <vector>
#include <algorithm>
#include "../Logger/Logger.h"

int Entity::GetId() const{
    return id;
}

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {

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

Entity Registry::CreateEntity() {
    int entityId = numEntities++;

    if (entityId >= entityComponentSignature.size()){
        entityComponentSignature.resize(entityId + 1);
    }

    Entity entity(entityId);
    entitiesToBeAdded.insert(entity);
    Logger::Log("Entity created with ID - " + std::to_string(entityId));

    return entity;
}

void Registry::Update() {
    //TODO: Add the entities that are waiting to be created to the active Systems
    //TODO: Remove all the entities that are waiting to be killed
}
