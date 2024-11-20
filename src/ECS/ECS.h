#pragma once
#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

////////////////////////////////////////////////////////////////////////////////////////
// Signature
////////////////////////////////////////////////////////////////////////////////////////
// A bitset (collection of 0s and 1s) is used to keep a track of the components
// related to an entity. Also keeps tracks of the entities a system is interested in.
////////////////////////////////////////////////////////////////////////////////////////
typedef std::bitset<MAX_COMPONENTS> Signature;


// Interface for component
struct IComponent{
    protected:
        static int nextId;
};

// Used to assign a unique ID for each component type.
template <typename T>
class Component: public IComponent{
    // Returns the unique ID of Component<T>
    static int GetId(){
        static auto id = nextId++;
        return id;
    }
};

////////////////////////////////////////////////////////////////////////////////////////
// Entity
////////////////////////////////////////////////////////////////////////////////////////
// The Entity object will simply be a numerical identifier of an entity.
////////////////////////////////////////////////////////////////////////////////////////
class Entity {
    private:
        int id;
    
    public:
        Entity(int id): id(id) {};
        int GetId() const;
}; 

////////////////////////////////////////////////////////////////////////////////////////
// System
////////////////////////////////////////////////////////////////////////////////////////
// System processes entities that contain a specific "signature" (a bitset).
////////////////////////////////////////////////////////////////////////////////////////
class System {
    private:
        Signature componentSingature; // Components required by the system.
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;
        Signature& GetComponentSignature() const;


        // Defines the component type T that entities must have to be considered by the system.
        template <typename T> void RequireComponent();
};

class Registry {
     
};

template <typename T>
void System::RequireComponent(){
    const auto componentId = Component<T>.GetId();
    componentSingature.set(componentId);

}