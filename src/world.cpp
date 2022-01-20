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

    call_member_for_every_object(&entity::on_update);
}


void world::start()
{
    // Some starting work
    // ...

    call_member_for_every_object(&entity::on_start);
}

void world::end()
{
    // Some ending work
    // ...

    call_member_for_every_object(&entity::on_end);
}

std::shared_ptr<entity> world::get_entity(const entity_id& entity_id) const
{
    return object_map_.at(entity_id);
}

world::world()
{
}

};