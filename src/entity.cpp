#include "entity.h"
#include "trait.h"

namespace rela{

entity::entity(const entity_id& entity_id) : entity(entity_id, {0,0}, {})
{

}

entity::entity(const entity_id& entity_id, point postion): entity(entity_id, postion, {})
{

}

entity::entity(const entity_id& entity_id, std::initializer_list<std::weak_ptr<trait>> traits_list): 
    entity(entity_id, {0,0}, traits_list)
{
}

entity::entity(const entity_id& entity_id, point postion, std::initializer_list<std::weak_ptr<trait>> traits_list) : 
    id_interface(entity_id.str()), pos_(postion)
{
    for (auto &&i : traits_list)
    {
        add_object(i);
    }
}

entity::~entity()
{

}

entity::entity(entity&& e) noexcept : id_interface(std::move(e)), object_manager_interface(std::move(e)), pos_(std::move(e.pos_))
{
}

entity& entity::operator=(entity&& e) noexcept
{
    if (this != &e)
    {
        id_interface::operator=(std::move(e));
        object_manager_interface::operator=(std::move(e));
        pos_ = std::move(e.pos_);
    }
    return *this;
}


const point& entity::get_pos() const
{
    return pos_;
}

void entity::set_pos(const point& new_pos)
{
    pos_ = new_pos;
}

void entity::on_update()
{
    call_member_for_every_object(&trait::on_update, this);
}

void entity::on_start()
{
    call_member_for_every_object(&trait::on_start, this);
}

void entity::on_end()
{
    call_member_for_every_object(&trait::on_end, this);
}


}//rela