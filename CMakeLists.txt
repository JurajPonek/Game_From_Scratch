cmake_minimum_required(VERSION 3.22)
project(game
        VERSION "0.0.1"
        LANGUAGES C CXX
        )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(src)
include(FetchContent)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master      
    GIT_SHALLOW    TRUE        
)

FetchContent_MakeAvailable(stb)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})

target_link_libraries(game PRIVATE stb)


