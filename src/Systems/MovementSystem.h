#pragma once
#include "../ECS/ECS.h"

class MovementSystem: public System {
    public:
        MovementSystem(){
            // RequireComponent<TransformComponent>(); -> I only want entities with the transform component.
            // RequireComponent<...>();
           
        }
        
        void Update(){ // Logic that will be called each frame.
            // TODO: Loop all entities the system is interested in
            //
            // for (auto entity: GetEntities()){
                // TODO: Update entity position
            // }
        }
};