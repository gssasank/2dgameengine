#pragma once
#include "../ECS/ECS.h"

class MovementSystem: public System {
    public:
        MovementSystem(){
            // RequireComponent<TransformComponnet>();
            // RequireComponent<...>();
           
        }
        
        void Update(){
            // TODO: Loop all entities the system is interested in
            //
            // for (auto entity: GetEntities()){
                // TODO: Update entity position
            // }
        }
};