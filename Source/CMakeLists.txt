add_executable(RayTracer
    Main.cpp
    Matrix.cpp
    Sphere.cpp
)

target_link_libraries(RayTracer PRIVATE RayTracer_Headers)
