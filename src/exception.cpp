#include "exception.hpp"
#include <stacktrace>
#include <stdexcept>
#include <string>
#include <ranges>

namespace game
{
    Exception::Exception(const std::string& what) 
        : std::runtime_error(what), m_trace(std::stacktrace::current(1))
    {

    }
    std::string Exception::stacktrace() const
    {
        return std::to_string(m_trace);
    }
}