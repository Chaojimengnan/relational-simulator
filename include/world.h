#pragma once
#include "relafwd.h"
#include "utility.h"


namespace rela{

class world : protected object_manager_interface<entity, std::shared_ptr>
{
public:
    static world& instance();

    // Update the world!
    void update();

    // Start the world!
    void start();

    // End the world!
    void end();

    // Calls the specified function for each entity
    template<typename Func>
    void enumerate_entities(Func enumerate_func);
    
    [[nodiscard]] std::shared_ptr<entity> get_entity(const entity_id& entity_id) const;

public:
    void add_entity(ptr_type new_object) {
        object_manager_interface::add_object(new_object);
    }
    void remove_entity(const string_id<object_type>& object_id) noexcept {
        object_manager_interface::remove_object(object_id);
    }
    bool has_same_entity(const string_id<object_type>& object_id) const {
        return object_manager_interface::has_same_object(object_id);
    }
    void clear_entities() noexcept {
        object_manager_interface::clear_objects();
    }
    size_type entity_counts() const noexcept {
        return object_manager_interface::objects_counts();
    }

private:
    world();
};

template<typename Func>
void world::enumerate_entities(Func enumerate_func)
{
    for (auto &&i : object_map_)
        enumerate_func(i.second);
}

}//rela

