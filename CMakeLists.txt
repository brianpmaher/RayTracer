cmake_minimum_required(VERSION 3.28)

project(RayTracer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

function(add_dependency name repository tag)
    FetchContent_Declare(
        ${name}
        GIT_REPOSITORY ${repository}
        GIT_TAG ${tag}
    )
    FetchContent_MakeAvailable(${name})
endfunction()

add_dependency(Catch2 https://github.com/catchorg/Catch2.git v3.10.0)

add_executable(RayTracer
    Source/Main.cpp
)

