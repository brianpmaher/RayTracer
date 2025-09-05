cmake_minimum_required(VERSION 3.28)

project(RayTracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.10.0
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_subdirectory(Include)
add_subdirectory(Source)
add_subdirectory(Tests)
