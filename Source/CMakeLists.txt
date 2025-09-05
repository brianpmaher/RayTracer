add_library(RayTracer_Lib
    Matrix.cpp
    Sphere.cpp
)

target_link_libraries(RayTracer_Lib PRIVATE RayTracer_Headers)

add_executable(RayTracer
    Main.cpp
)

target_link_libraries(RayTracer PRIVATE RayTracer_Lib)
