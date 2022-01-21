#pragma once

namespace rela{

class world;
class entity;
class trait;
class entity_group;

template<typename T>
class string_id;

using entity_id = string_id<entity>;
using trait_id = string_id<trait>;
using entity_group_id = string_id<entity_group>;

}//rela