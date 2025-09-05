cmake_minimum_required(VERSION 3.28)

project(RayTracer LANGUAGES CXX)

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

add_executable(${PROJECT_NAME}
    Source/Main.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        Include
)

add_dependency(Catch2 https://github.com/catchorg/Catch2.git v3.10.0)

set(TEST_PROJECT ${PROJECT_NAME}_Tests)

add_executable(${TEST_PROJECT}
    Tests/Math/Vector3.cpp
)

target_include_directories(${TEST_PROJECT}
    PUBLIC
        Include
)

target_link_libraries(${TEST_PROJECT} PRIVATE Catch2::Catch2WithMain)
