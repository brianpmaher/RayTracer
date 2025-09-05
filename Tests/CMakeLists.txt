add_executable(RayTracer_Tests
    Vector3.cpp
    Vector4.cpp
    Color.cpp
    Matrix.cpp
    Ray.cpp
    Sphere.cpp
    ../Source/Matrix.cpp
    ../Source/Sphere.cpp
)

target_link_libraries(RayTracer_Tests
    PRIVATE
        Catch2::Catch2WithMain
        RayTracer_Headers
)

add_test(NAME RayTracer_Tests COMMAND RayTracer_Tests)
