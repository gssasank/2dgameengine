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
        static int nextId; //! Static variables only get initialized once!!
};

// Used to assign a unique ID for each component type T, not for each specific component. Eg., we would like to have an AI system on all the components of a specific type, and we will not specify this for each component.
template <typename T> 
class Component: public IComponent{
    // Returns the unique ID of Component<T>. 
    static int GetId(){
        static auto id = nextId++; //! Since static variables get initialized only once, each unique component type will get the same value back. This line will only run the first time.
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

        bool operator ==(const Entity& otherEntity) const { return id == otherEntity.id; }
        bool operator !=(const Entity& otherEntity) const { return id =!= otherEntity.id; }

}; 

////////////////////////////////////////////////////////////////////////////////////////
// System
////////////////////////////////////////////////////////////////////////////////////////
// System processes entities that contain a specific "signature" (a bitset).
////////////////////////////////////////////////////////////////////////////////////////
class System {
    private:
        Signature componentSignature; // So that system knows which entity to act upon. Unique entities will have specific component signatures.
        std::vector<Entity> entities; // List of entities that a system is interested in.

    public:
        System() = default;
        ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const; // const added because they only return values and they do not modify anything.
        const Signature& GetComponentSignature() const; // const added because they only return values and they do not modify anything.

        // Defines the component type T that entities must have to be considered by the system.
        template <typename TComponent> void RequireComponent();
};

class Registry {
     
};

template <typename TComponent>
void System::RequireComponent(){
    const auto componentId = Component<TComponent>().GetId();
    componentSignature.set(componentId);
}
