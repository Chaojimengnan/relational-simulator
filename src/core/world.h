#pragma once
#include "relafwd.h"
#include "utility.h"


namespace rela{

class world : protected object_manager_interface<entity, std::shared_ptr>, protected object_manager_interface<entity_group, std::shared_ptr>
{
public:
    using entity_base = object_manager_interface<entity, std::shared_ptr>;
    using group_base = object_manager_interface<entity_group, std::shared_ptr>;

    static world& instance();

    // Calls the specified function for each entity
    template<typename Func>
    void enumerate_entities(Func enumerate_func);
    
    [[nodiscard]] std::shared_ptr<entity> get_entity(const entity_id& entity_id) const;

public:
    // Update the world!
    void update();

    // Start the world!
    void start();

    // End the world!
    void end();

public:
    void add_entity(std::shared_ptr<entity> new_entity) {
        entity_base::add_object(new_entity);
    }
    void remove_entity(const entity_id& entity_id) noexcept {
        entity_base::remove_object(entity_id);
    }
    bool has_same_entity(const entity_id& entity_id) const {
        return entity_base::has_same_object(entity_id);
    }
    void clear_entities() noexcept {
        entity_base::clear_objects();
    }
    entity_base::size_type entity_counts() const noexcept {
        return entity_base::objects_counts();
    }

    // TODO: entity_group interface

private:
    world();
};

template<typename Func>
void world::enumerate_entities(Func enumerate_func)
{
    for (auto &&i : entity_base::object_map_)
        enumerate_func(i.second);
}

}//rela

