#pragma once
#include <stdexcept>
#include <string_view>
#include <fmt/format.h>
#include <cassert>

namespace rela{

// Throw when the object being inserted has the same string id with the objects map
class has_same_string_id_error : public std::exception
{
public:
   has_same_string_id_error(std::string_view  string_id)
        : what_str(fmt::format("The object map already has the object with same id : {}", string_id))
    {
    }

    const char* what() const noexcept override
    {
        return what_str.c_str();
    }
private:
    std::string what_str;
};

// Throw when data in the stream cannot be converted to Point
class stream_to_point_error : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Data in the stream cannot be converted to point";
    }
};


}//rela