#pragma once
#include <memory>
#include <unordered_map>
#include "relafwd.h"
#include "utility.h"

namespace rela{


class trait_manager : public object_manager_interface<trait, std::shared_ptr>{
public:
    static trait_manager& instance();
    [[nodiscard]] std::weak_ptr<trait> get_trait(const trait_id& trait_id);

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