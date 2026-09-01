#pragma once
#include <print>
#include <format>
#include <source_location>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

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
        std::string_view format;
        std::source_location loc;
        log(const char* s, std::source_location location = std::source_location::current()) 
            : format(s), loc(location) {}
    };

    template<Level L, typename... Args>
    void print(log message, Args&&... args) 
    {
        const std::vector<std::pair<std::string, std::string>> levels = {{"\033[34m", "DEBUG"}, {"\033[32m","INFO"}, {"\033[33m", "WARNING"}, {"\033[31m","ERROR"}};
        auto level = levels[static_cast<int>(L)];
        std::println("{} [{}] {}:{} {} \033[37m", level.first, level.second, message.loc.file_name(), message.loc.line(), std::vformat(message.format, std::make_format_args(args...)));
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