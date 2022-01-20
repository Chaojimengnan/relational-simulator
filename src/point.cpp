#include "point.h"
#include <fmt/format.h>
#include <sstream>
#include "exception.h"


namespace rela{

std::string point::to_string() const
{
    return fmt::format("({},{})", x, y);
}

std::ostream& operator<<(std::ostream& lhs, const point& rhs)
{
	return lhs << rhs.to_string();
}

std::istream& operator>>(std::istream& in, point& rhs)
{
    char c;
	if (!(in.get(c) &&c == '(' && in >> rhs.x && in.get(c) && c == ',' && in >> rhs.y &&
                                in.get(c) &&c == ')'))
		throw stream_to_point_error();
	return in;
}

point point::from_string(std::string_view str)
{
    std::istringstream in(str.data());
    point p;
    in >> p;
	return p;
}

}//rela