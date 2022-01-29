#pragma once
#include "relafwd.h"
#include "utility.h"

namespace rela{


class trait_manager{
public:
    using trait_map_t = object_manager_interface<trait, std::shared_ptr>;
    static trait_manager& instance();

public:
    void add_trait(trait_map_t::ptr_type new_trait) {
        trait_map_.add_object(new_trait);
    }
    void remove_trait(const trait_id& trait_id) noexcept {
       trait_map_.remove_object(trait_id);
    }
    bool has_trait(const trait_id& trait_id) const {
        return trait_map_.has_object(trait_id);
    }
    [[nodiscard]] std::weak_ptr<trait> get_trait(const trait_id& trait_id)
    {
        return trait_map_.get_object(trait_id);
    }
    void clear_traits() noexcept {
        trait_map_.clear_objects();
    }
    trait_map_t::size_type trait_counts() const noexcept {
        return trait_map_.objects_counts();
    }

private:
    trait_map_t trait_map_;
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