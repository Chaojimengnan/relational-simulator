#include <sstream>
#include "entity.h"
#include "trait.h"

namespace rela{

entity::entity(const entity_id& entity_id) : entity(entity_id, {0,0}, {})
{

}

entity::entity(const entity_id& entity_id, point postion): entity(entity_id, postion, {})
{

}

entity::entity(const entity_id& entity_id, std::initializer_list<trait_id> traits_list): 
    entity(entity_id, {0,0}, traits_list)
{
}

entity::entity(const entity_id& entity_id, point postion, std::initializer_list<trait_id> traits_list) : 
    id_interface(entity_id.str()), pos_(postion)
{
    auto trait_manager = trait_manager::instance();
    for (auto &&trait_id : traits_list)
    {
        add_object(trait_manager.get_trait(trait_id));
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


entity_group::entity_group(std::initializer_list<entity_id> entities_list) : id_interface("")
{
    std::ostringstream o;
    for (auto &&i : entities_list)
    {
        o << i.str() << ",";
    }

    id_ = static_cast<entity_group_id>(o.str());
}

entity_group::~entity_group()
{
}

entity_group::entity_group(entity_group&& rhs) : id_interface(std::move(rhs)), object_manager_interface(std::move(rhs))
{
}

entity_group& entity_group::operator=(entity_group&& rhs)
{
    if (this != &rhs)
    {
        id_interface::operator=(std::move(rhs));
        object_manager_interface::operator=(std::move(rhs));
    }
    return *this;   
}

std::vector<entity_id> entity_group::get_entity_id_list() const
{
    std::vector<entity_id> entity_id_list;
    for (auto &&[entity_id, entity] : object_map_)
    {
        entity_id_list.push_back(entity_id);
    }
    return entity_id_list;
}


}//rela