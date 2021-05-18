#ifndef _ECS_H_
#define _ECS_H_

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using Group = std::size_t;
using ComponentID = std::size_t;

inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using GroupBitSet = std::bitset<maxGroups>;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component
{
public:
    // reference to its owner
    Entity *entity;

    virtual void Init() {}
    virtual void Update() {}
    virtual void Draw() {}

    virtual ~Component() {}
};

class Entity
{
private:
    Manager &manager;
    bool active{true};
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

public:
    Entity(Manager &pManager) : manager{pManager} {}

    void Update()
    {
        // All components must be updated first then drawn
        // not each component updated and drawn
        for (auto &c : components)
            c->Update();
    }

    void Draw()
    {
        for (auto &c : components)
            c->Draw();
    }

    bool isActive() const { return active; }

    bool hasGroup(Group group)
    {
        return groupBitSet[group];
    }

    void AddGroup(Group group);
    void DelGroup(Group group)
    {
        groupBitSet[group] = false;
    }

    void Destroy()
    {
        active = false;
    }

    template <typename T>
    bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T &AddComponent(TArgs &&... mArgs)
    {
        // Create an object pointer (c) of type (T)
        // forwarding (mArgs) to the constructor of (c)
        // note: std::forward lets us pass margs as either lvalues or rvalues
        // depending on the needs of the constructor for (c)
        T *c(new T(std::forward<TArgs>(mArgs)...));

        // Assume (c) is a component, which has an entity member i.e. the reference to its owner
        // which we will assign to (this)
        c->entity = this;

        // create a unique pointer
        // use unique pointer to disable accidental re-assigning or copying
        std::unique_ptr<Component> uPtr{c};
        // and move the contents of uPtr to the component vector std::move deletes uPtr
        // effectively passing ownership from (uPtr) to (components)
        components.emplace_back(std::move(uPtr));
        // components.emplace_back(std::unique_ptr{c});

        // set the array element in the (componentArray) at (typeID) for (c) to (c)
        componentArray[getComponentTypeID<T>()] = c;
        // set the bit in (componentBitSet) at (typeID) for (c) to true
        componentBitSet[getComponentTypeID<T>()] = true;

        c->Init();
        return *c;
    }

    template <typename T>
    T &GetComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        // return (ptr), whatever it is, as a (T) so that methods of T can be called
        // like so: gameObject.getComponent<PositionComponent>().setXPos(...);
        return *static_cast<T *>(ptr);
    }
};

class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity *>, maxGroups> groupedEntities;

public:
    void Update()
    {
        for (auto &e : entities)
        {
            e->Update();
        }
    }

    void Draw()
    {
        for (auto &e : entities)
        {
            e->Draw();
        }
    }

    // Remove entities that are not set active
    void Refresh()
    {
        // remove inactive entities from groups
        for (auto i{0u}; i < maxGroups; i++)
        {
            auto &v(groupedEntities[i]);
            v.erase(
                std::remove_if(v.end(), v.begin(), [i](Entity *e) { return !e->isActive() || !e->hasGroup(i); }),
                v.end());
        }

        // erase removes elements from start - in this case the pointer that (remove_if) will return
        // to (entities.end())
        entities.erase(
            std::remove_if(
                entities.begin(), entities.end(), [](const auto &e) { return !e->isActive(); }),
            entities.end());
    }

    void AddToGroup(Entity* e, Group g)
    {
        groupedEntities[g].emplace_back(e);
    }

    std::vector<Entity*> &GetGroup(Group g)
    {
        return groupedEntities[g];
    }

    Entity &AddEntity()
    {
        // Entity* e = new Entity();
        // std::unique_ptr<Entity> uPtr{e};
        // entities.emplace_back(std::move(uPtr));
        entities.emplace_back(std::make_unique<Entity>(*this));

        return *entities.back();
    }
};

#endif