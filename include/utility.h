#pragma once
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "exception.h"
#include "relafwd.h"

namespace rela{

// Simple encapsulation of std::string
// Use the type system to ensure that the ID belongs to the specified class
template<typename T>
class string_id
{
public:
    explicit string_id(std::string_view id);
    string_id(const string_id&);
    string_id(string_id&&) noexcept;
    ~string_id();

    string_id& operator=(const string_id&);
    string_id& operator=(string_id&&) noexcept;

public:
    explicit operator std::string() const;
    const std::string& str() const;

private:
    std::string id_;    
};

template<typename T>
string_id<T>::string_id(std::string_view id) : id_(id)
{

}

template<typename T>
string_id<T>::string_id(const string_id& si) : id_(si.id_)
{
}

template<typename T>
string_id<T>::string_id(string_id&& si) noexcept : id_(std::move(si.id_))
{

}

template<typename T>
string_id<T>::~string_id()
{
}

template<typename T>
string_id<T>& string_id<T>::operator=(const string_id& si)
{
    id_ = si.id_;
}

template<typename T>
string_id<T>& string_id<T>::operator=(string_id&& si) noexcept
{
    id_ = std::move(si.id_);
    return *this;
}

template<typename T>
string_id<T>::operator std::string() const
{
    return id_;
}

template<typename T>
const std::string& string_id<T>::str() const
{
    return id_;
}

template<typename T>
bool operator==(const string_id<T>& lhs, const string_id<T>& rhs) noexcept
{
    return lhs.str() == rhs.str();
}

template<typename T>
bool operator!=(const string_id<T>& lhs, const string_id<T>& rhs) noexcept
{
    return lhs.str() != rhs.str();
}

// Makes the class that inherits this to get a string ID
template<typename T>
class id_interface{
public:
    id_interface(std::string_view);
    const string_id<T>& get_id() const;

protected:
    string_id<T> id_;
};

template<typename T>
id_interface<T>::id_interface(std::string_view sv) : id_(sv)
{}

template<typename T>
const string_id<T>& id_interface<T>::get_id() const
{
    return id_;
}


// Makes classes that inherit from this to manage the specified object
template<typename T, template<typename> typename U>
class object_manager_interface{
public:
    using object_type = T;
    using ptr_type = U<T>;
    using size_type = typename std::unordered_map<string_id<object_type>, ptr_type>::size_type;

    void add_object(ptr_type new_object);
    void remove_object(const string_id<object_type>& object_id) noexcept;
    bool has_same_object(const string_id<object_type>& object_id) const;
    void clear_objects() noexcept;
    size_type objects_counts() const noexcept;

protected:
    // Call the member function for every object in the manager
    template<typename MemberType, typename... Args>
    void call_member_for_every_object(MemberType member_func, Args&&... args);

    std::unordered_map<string_id<object_type>, ptr_type> object_map_;
};

template<typename T, template<typename> typename U>
void object_manager_interface<T, U>::add_object(ptr_type new_object)
{
    // Because weak_ptr cannot get the ID directly, 
    // so it's necessary to check if it is weak_ptr and special handling
    if constexpr (std::is_same_v<ptr_type, std::weak_ptr<T>>)
    {
        if (!new_object.expired())
        {
            auto new_object_ptr = new_object.lock();
            auto object_id = new_object_ptr->get_id();
            if (!object_map_.insert(std::make_pair(object_id, std::move(new_object))).second)
            {
                throw has_same_string_id_error(object_id.str());
            }
        }
    } else {
        auto object_id = new_object->get_id();
        if (!object_map_.insert(std::make_pair(object_id, std::move(new_object))).second)
        {
            throw has_same_string_id_error(object_id.str());
        }
    }
    
}


template<typename T, template<typename> typename U>
void object_manager_interface<T, U>::remove_object(const string_id<object_type>& object_id) noexcept
{
    object_map_.erase(object_id);
}

template<typename T, template<typename> typename U>
bool object_manager_interface<T, U>::has_same_object(const string_id<object_type>& object_id) const
{
    return object_map_.find(object_id) != object_map_.cend();
}

template<typename T, template<typename> typename U>
void object_manager_interface<T, U>::clear_objects() noexcept
{
    object_map_.clear();
}

template<typename T, template<typename> typename U>
typename object_manager_interface<T, U>::size_type object_manager_interface<T, U>::objects_counts() const noexcept
{
    return object_map_.size();
}

template<typename T, template<typename> typename U>
template<typename MemberType, typename... Args>
void object_manager_interface<T, U>::call_member_for_every_object(MemberType member_func, Args&&... args)
{
    static_assert(std::is_member_function_pointer_v<MemberType>, 
        "member_func must be a member function pointer!");

    // weak_ptr is different from other pointers, so treated specially
    if constexpr(std::is_same_v<ptr_type, std::weak_ptr<T>>)
    {
        std::vector<string_id<object_type>> expired_list;
        for (auto &&[object_id, object] : object_map_)
        {
            if (!object.expired())
            {
                auto object_ptr = object.lock();
                // Unfortunately, smart pointer doesn't support '->*'
                ((*object_ptr).*member_func)(std::forward<Args>(args)...);
            } else {
                expired_list.push_back(object_id);
            }
        }

        for (auto &&object_id : expired_list)
            remove_object(object_id);

    // Other pointers
    } else {

        for (auto &&[object_id, object] : object_map_)
            ((*object).*member_func)(std::forward<Args>(args)...);

    }
}

}//rela


namespace std{
    template<typename T>
    struct hash<rela::string_id<T>>
    {
        size_t operator()(const rela::string_id<T>& str_id) const noexcept
        {
            return std::hash<std::string>()(str_id.str());
        }
    };
}//std


