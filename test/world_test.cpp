#include "gtest/gtest.h"
#include "relafwd.h"
#include "utility.h"
#include "entity.h"
#include "world.h"
#include "exception.h"

using namespace rela;

TEST(world_test, base_test) 
{
    auto my_world = world::instance();
    std::vector<entity_id> entity_id_vec = {
        entity_id("Meng Nan"),
        entity_id("Long Long"),
        entity_id("My My")
    };

    EXPECT_NO_THROW(
        for (auto &&entity_id_val : entity_id_vec)
            my_world.add_object(std::make_shared<entity>(entity_id_val));
    );

    EXPECT_EQ(my_world.objects_size(), 3);

    EXPECT_THROW(my_world.add_object(std::make_shared<entity>(static_cast<entity_id>("Meng Nan"))), has_same_string_id_error);

    EXPECT_NO_THROW(my_world.remove_object(entity_id("abc")));

    EXPECT_FALSE(my_world.has_same_object(entity_id("abc")));
    EXPECT_TRUE(my_world.has_same_object(entity_id("Meng Nan")));

    auto meng_nan = my_world.get_entity(entity_id("Meng Nan"));
    EXPECT_THROW(my_world.add_object(meng_nan), has_same_string_id_error);
    
    my_world.enumerate_entities([&entity_id_vec](const std::shared_ptr<entity>& entitys){
        EXPECT_NE(std::find(entity_id_vec.cbegin(), entity_id_vec.cend(), entitys->get_id()), entity_id_vec.cend());
    });

    my_world.clear_objects();

    EXPECT_EQ(my_world.objects_size(), 0);
}

