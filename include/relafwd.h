#pragma once

namespace rela{

class world;
class entity;
class trait;

template<typename T>
class string_id;

using entity_id = string_id<entity>;
using trait_id = string_id<trait>;

}//rela