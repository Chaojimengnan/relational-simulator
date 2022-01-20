#pragma once
#include <memory>
#include "relafwd.h"
#include "utility.h"


namespace rela{

class world : public object_manager_interface<entity, std::shared_ptr>
{
public:
    static world& instance();

    // Update the world!
    void update();

    // Start the world!
    void start();

    // End the world!
    void end();

    // Calls the specified function for each entity
    template<typename Func>
    void enumerate_entities(Func enumerate_func);
    
    [[nodiscard]] std::shared_ptr<entity> get_entity(const entity_id& entity_id) const;

private:
    world();
};

template<typename Func>
void world::enumerate_entities(Func enumerate_func)
{
    for (auto &&i : object_map_)
        enumerate_func(i.second);
}

}//rela

