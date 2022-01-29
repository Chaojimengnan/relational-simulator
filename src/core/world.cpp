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

    entity_map_.call_member_for_every_object(&entity::on_update);
}


void world::start()
{
    // Some starting work
    // ...

    entity_map_.call_member_for_every_object(&entity::on_start);
}

void world::end()
{
    // Some ending work
    // ...

    entity_map_.call_member_for_every_object(&entity::on_end);
}

world::world()
{
}

};