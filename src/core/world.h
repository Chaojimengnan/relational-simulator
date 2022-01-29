#pragma once
#include "relafwd.h"
#include "utility.h"


namespace rela{

class world
{
public:
    using entity_map_t = object_manager_interface<entity, std::shared_ptr>;
    static world& instance();

    // Calls the specified function for each entity
    template<typename Func>
    void enumerate_entities(Func enumerate_func);

public:
    // Update the world!
    void update();

    // Start the world!
    void start();

    // End the world!
    void end();

public:
    void add_entity(std::shared_ptr<entity> new_entity) {
        entity_map_.add_object(new_entity);
    }
    void remove_entity(const entity_id& entity_id) noexcept {
        entity_map_.remove_object(entity_id);
    }
    bool has_entity(const entity_id& entity_id) const {
        return entity_map_.has_object(entity_id);
    }
    [[nodiscard]] std::shared_ptr<entity> get_entity(const entity_id& entity_id)
    {
        return entity_map_.get_object(entity_id);
    }
    void clear_entities() noexcept {
        entity_map_.clear_objects();
    }
    entity_map_t::size_type entity_counts() const noexcept {
        return entity_map_.objects_counts();
    }

private:
    entity_map_t entity_map_;
    world();
};

template<typename Func>
void world::enumerate_entities(Func enumerate_func)
{
    for (auto &&i : entity_map_.object_map_)
        enumerate_func(i.second);
}

}//rela

