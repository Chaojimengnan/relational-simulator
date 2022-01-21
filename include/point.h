#pragma once
#include <cmath>
#include <utility>
#include <string>
#include <string_view>
#include <iostream>

namespace rela{

struct point
{
    constexpr point() = default;
    constexpr point(int x, int y): x(x), y(y){}
    constexpr point(std::pair<int, int> pos): x(pos.first), y(pos.second) {}
    
    constexpr point operator-() const noexcept {
        return point(-x, -y);
    }

    constexpr point& operator+=(const point& rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    constexpr point& operator-=(const point& rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    double distance() const noexcept {
        return std::sqrt(x * x + y * y);
    }

    constexpr size_t distance_rough() const noexcept {
        return x * x + y * y;
    }

    constexpr point abs() const noexcept {
        return point(std::abs(x), std::abs(y));
    }

    std::string to_string() const;

    static point from_string(std::string_view str);

    int x = 0;
    int y = 0;
};

constexpr point operator+(const point& lhs, const point& rhs) noexcept
{
    return point(lhs.x + rhs.x, lhs.y + rhs.y);
}

constexpr point operator-(const point& lhs, const point& rhs) noexcept
{
    return point(lhs.x - rhs.x, lhs.y - rhs.y);
}

constexpr bool operator==(const point& lhs, const point& rhs) noexcept
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

constexpr bool operator!=(const point& lhs, const point& rhs) noexcept
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& lhs, const point& rhs);

std::istream& operator>>(std::istream& in, point& rhs);

}//rela