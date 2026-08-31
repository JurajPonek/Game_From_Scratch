#pragma once
#include <print>
#include <format>
#include <source_location>

#ifdef ERROR
#undef ERROR
#endif

namespace game::log 
{

    enum class Level 
    {   DEBUG, 
        INFO, 
        WARNING, 
        ERROR 
    };


    struct log 
    {
        std::string_view fmt;
        std::source_location loc;
        log(const char* s, std::source_location l = std::source_location::current()) 
            : fmt(s), loc(l) {}
    };

    template<Level L, typename... Args>
    void print(log message, Args&&... args) 
    {
        const char* levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
        
        std::println("[{}] {}:{} {}", levels[static_cast<int>(L)], message.loc.file_name(), message.loc.line(), std::vformat(message.fmt, std::make_format_args(args...)));
    }

    template<typename... Args> 
    void debug(log message, Args&&... args) 
    { 
        print<Level::DEBUG>(message, std::forward<Args>(args)...); 
    }

    template<typename... Args> 
    void error(log message, Args&&... args) 
    { 
        print<Level::ERROR>(message, std::forward<Args>(args)...); 
    }

    template<typename... Args> 
    void info(log message, Args&&... args)  
    { 
        print<Level::INFO>(message, std::forward<Args>(args)...); 
    }

    template<typename... Args> 
    void warn(log message, Args&&... args)  
    { 
        print<Level::WARNING>(message, std::forward<Args>(args)...); 
    }
}