#pragma once
#include "relafwd.h"
#include "utility.h"
#include "trait.h"
#include "point.h"

namespace rela{

class entity : public id_interface<entity>, protected object_manager_interface<trait, std::weak_ptr>
{
    friend class world;
public:
    entity(const entity_id& entity_id);
    entity(const entity_id& entity_id, point postion);
    entity(const entity_id& entity_id, std::initializer_list<std::weak_ptr<trait>> traits_list);
    entity(const entity_id& entity_id, point postion, std::initializer_list<std::weak_ptr<trait>> traits_list);

    virtual ~entity();

    entity(const entity&) = delete;
    entity& operator=(const entity&) = delete;

    entity(entity&&) noexcept;
    entity& operator=(entity&&) noexcept;

public:
    const point& get_pos() const;
    void set_pos(const point& new_pos);

public:
    void add_trait(ptr_type new_object) {
        object_manager_interface::add_object(new_object);
    }
    void remove_trait(const string_id<object_type>& object_id) noexcept {
        object_manager_interface::remove_object(object_id);
    }
    bool has_same_trait(const string_id<object_type>& object_id) const {
        return object_manager_interface::has_same_object(object_id);
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

private:
    point pos_;

};



class entity_group
{
public:

};

}//rela

