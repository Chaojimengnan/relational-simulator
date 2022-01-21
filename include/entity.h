#pragma once
#include "relafwd.h"
#include "utility.h"
#include "trait.h"
#include "point.h"

namespace rela{

class entity : public id_interface<entity>, private object_manager_interface<trait, std::weak_ptr>
{
    friend class world;
public:
    entity(const entity_id& entity_id);
    entity(const entity_id& entity_id, point postion);
    entity(const entity_id& entity_id, std::initializer_list<trait_id> traits_list);
    entity(const entity_id& entity_id, point postion, std::initializer_list<trait_id> traits_list);

    virtual ~entity();

    entity(const entity&) = delete;
    entity& operator=(const entity&) = delete;

    entity(entity&&) noexcept;
    entity& operator=(entity&&) noexcept;

public:
    const point& get_pos() const;
    void set_pos(const point& new_pos);

public:
    void add_trait(const trait_id& trait_id) {
        object_manager_interface::add_object(trait_manager::instance().get_trait(trait_id));
    }
    void remove_trait(const trait_id& trait_id) noexcept {
        object_manager_interface::remove_object(trait_id);
    }
    bool has_same_trait(const trait_id& trait_id) const {
        return object_manager_interface::has_same_object(trait_id);
    }
    void clear_traits() noexcept {
        object_manager_interface::clear_objects();
    }
    size_type trait_counts() const noexcept {
        return object_manager_interface::objects_counts();
    }

protected:
    // Called when the world is updated
    virtual void on_update();
    
    // Called when the world starts
    virtual void on_start();

    // Called when the world ends
    virtual void on_end();

protected:
    using object_manager_interface::call_member_for_every_object;
    using object_manager_interface::object_map_;

private:
    point pos_;

};

class entity_group : public id_interface<entity_group>, private object_manager_interface<entity, std::weak_ptr>
{
    friend class world;
public:
    entity_group(std::initializer_list<entity_id> entities_list);

    virtual ~entity_group();

    entity_group(const entity_group&) = delete;
    entity_group& operator=(const entity_group&) = delete;

    entity_group(entity_group&&);
    entity_group& operator=(entity_group&&);

public:
    bool has_same_entity(const entity_id& entity_id) const {
        return object_manager_interface::has_same_object(entity_id);
    }
    size_type entity_counts() const noexcept {
        return object_manager_interface::objects_counts();
    }

public:
    std::vector<entity_id> get_entity_id_list() const;

protected:
    // // Called when the world is updated
    // virtual void on_update();
    
    // // Called when the world starts
    // virtual void on_start();

    // // Called when the world ends
    // virtual void on_end();

    // // Called when new entity is trying enter this group
    // virtual void on_try_enter(const entity_id&);

    // // Called when entity in this object_map_ is trying leave this group
    // virtual void on_try_leave(const entity_id&);

protected:
    using object_manager_interface::call_member_for_every_object;
    using object_manager_interface::object_map_;

public:
    // bool try_enter_group(const entity_id&);
    // bool try_leave_group(const entity_id&);
};

}//rela

