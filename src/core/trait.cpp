#include "trait.h"

namespace rela{

trait_manager& trait_manager::instance()
{
    static trait_manager tm;
    return tm;
}

trait_manager::trait_manager()
{
}

trait::trait(const trait_id& trait_id) : id_interface(trait_id.str())
{
}


trait::~trait()
{
}

void trait::on_update(entity*)
{
}

void trait::on_start(entity*)
{
}


void trait::on_end(entity*)
{
}


}//rela