add_executable(game main.cpp
                    window.cpp
                    shader.cpp
)
target_include_directories(game PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(game PRIVATE opengl32)
target_compile_features(game PUBLIC cxx_std_23)
target_compile_options(game PUBLIC 
    -Wall 
    -Werror 
    -Wno-unused-variable 
    -Wno-unused-function
)
