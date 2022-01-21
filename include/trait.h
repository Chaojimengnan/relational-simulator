#pragma once
#include "relafwd.h"
#include "utility.h"

namespace rela{


class trait_manager : protected object_manager_interface<trait, std::shared_ptr>{
public:
    static trait_manager& instance();

    [[nodiscard]] std::weak_ptr<trait> get_trait(const trait_id& trait_id);

public:
    void add_trait(ptr_type new_trait) {
        object_manager_interface::add_object(new_trait);
    }
    void remove_trait(const trait_id& trait_id) noexcept {
        object_manager_interface::remove_object(trait_id);
    }
    bool has_same_trait(const trait_id& trait_id) const {
        return object_manager_interface::has_same_object(trait_id);
    }
    void clear_traits() noexcept {
        object_manager_interface::clear_objects();
    }
    size_type trait_counts() const noexcept {
        return object_manager_interface::objects_counts();
    }

private:
    trait_manager();
};


class trait : public id_interface<trait>
{
public:
    trait(const trait_id& trait_id);
    virtual ~trait();

public:
    // Called when the world is updated
    virtual void on_update(entity*);

    // Called when the world starts
    virtual void on_start(entity*);

    // Called when the world ends
    virtual void on_end(entity*);
};



}//rela