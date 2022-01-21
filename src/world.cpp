#include "world.h"
#include "entity.h"

namespace rela{

world& world::instance()
{
    static world world_;
    return world_;
}


void world::update()
{
    // Some updating work
    // ...

    entity_base::call_member_for_every_object(&entity::on_update);
    // group_base::call_member_for_every_object(&entity_group::on_update);
}


void world::start()
{
    // Some starting work
    // ...

    entity_base::call_member_for_every_object(&entity::on_start);
    // group_base::call_member_for_every_object(&entity_group::on_start);
}

void world::end()
{
    // Some ending work
    // ...

    entity_base::call_member_for_every_object(&entity::on_end);
    // group_base::call_member_for_every_object(&entity_group::on_end);
}

std::shared_ptr<entity> world::get_entity(const entity_id& entity_id) const
{
    return entity_base::object_map_.at(entity_id);
}

world::world()
{
}

};