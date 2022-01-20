#include "gtest/gtest.h"
#include "relafwd.h"
#include "utility.h"
#include "entity.h"
#include "trait.h"
#include "world.h"
#include "exception.h"

using namespace rela;

// This trait makes the entity move {100, 100} distance when updated
class temp_trait : public trait
{
public:
    using trait::trait;
    void on_update(entity* e) override
    {
        auto pos = e->get_pos();
        pos += {100, 100};
        e->set_pos(pos);
    }
};

TEST(entity_test, raw_entity_test) 
{
    auto you = std::make_shared<entity>(entity_id("you"), std::make_pair(0,0));

    auto my_world = world::instance();
    my_world.add_object(you);

    EXPECT_EQ(you->get_id(), entity_id("you"));
    
    auto my_trait_manager = trait_manager::instance();
    my_trait_manager.add_object(std::make_shared<temp_trait>(trait_id("temp_trait")));

    you->add_object(my_trait_manager.get_trait(trait_id("temp_trait")));

    auto old_pos = you->get_pos() + point(100, 100);
    my_world.update();

    EXPECT_EQ(you->get_pos(), old_pos);
    
}