#pragma once
#include <memory>
#include "relafwd.h"
#include "utility.h"
#include "point.h"

namespace rela{

class entity : public id_interface<entity>, public object_manager_interface<trait, std::weak_ptr>
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

}//rela

