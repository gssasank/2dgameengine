#pragma once
#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

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
        bool operator !=(const Entity& otherEntity) const { return id != otherEntity.id; }
        bool operator <(const Entity& otherEntity) const { return id < otherEntity.id; }
        bool operator >(const Entity& otherEntity) const { return id > otherEntity.id; }

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
        std::vector<Entity> GetSystemEntities() const; // const added because they only return values, and they do not modify anything.
        const Signature& GetComponentSignature() const; // const added because they only return values, and they do not modify anything.

        // Defines the component type T that entities must have to be considered by the system.
        template <typename TComponent> void RequireComponent();
};

////////////////////////////////////////////////////////////////////////////////////////
// Pool
////////////////////////////////////////////////////////////////////////////////////////
// A pool is just a vector of objects of type T (vector is arranged in memory in a contiguous way).
////////////////////////////////////////////////////////////////////////////////////////
class IPool {
    public:
        virtual ~IPool() {}
};

template <typename T> // Templates are defined in the header file directly.
class Pool {
    private:
        std::vector<T> data;

    public:
        Pool(int size = 100) { data.resize(size); }

        virtual ~Pool() = default;

        bool isEmpty() const{
            return data.empty();
        }

        int GetSize() const{
            return data.size();
        }

        void Resize(int n){
            data.resize(n);
        }

        void Clear() {
            data.clear();
        }

        void Add(T object){
            data.push_back(object);
        }

        void Set(int index, T object){
            data[index] = object;
        }

        T& Get(int index){
            return static_cast<T&>(data[index]);
        }

        T& operator [](unsigned int index) {
            return data[index];
        }
};

////////////////////////////////////////////////////////////////////////////////////////
// Registry
////////////////////////////////////////////////////////////////////////////////////////
// Registry manages the creation and deletion of entities, as well as adding components
// and systems to entities.
////////////////////////////////////////////////////////////////////////////////////////
class Registry {
    private:
        // Keep track of how many entities are added to the scene.
        int numEntities = 0;
        std::set<Entity> entitiesToBeAdded; // Entities awaiting creation in the next registry update.
        std::set<Entity> entitiesToBeKilled; // Entities awaiting destruction in the next registry update.

        // A vector of component Pools, each pool contains all the data for a certain component type.
        // [vector index = ComponentType ID]
        // [Pool index = Entity ID]
        std::vector<IPool*> componentPools; // Since Pool class needs a type T, we are going to have a vector of the parent class (interface).

        // Vector of component signatures.
        // This signature lets us know which components are turned on for an entity.
        // [vector index = Entity ID]
        std::vector<Signature> entityComponentSignature;

        // Map of active systems.
        // [index = SystemType ID]
        std::unordered_map<std::type_index, System*> systems;

    public:
        Registry() = default;
        ~Registry() = default;

        Entity CreateEntity();
        void KillEntity(Entity entity);
        void Update();
        void AddEntityToSystem(Entity entity);

};

template <typename TComponent>
void System::RequireComponent(){
    const auto componentId = Component<TComponent>().GetId();
    componentSignature.set(componentId);
}
