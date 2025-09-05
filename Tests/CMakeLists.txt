add_executable(RayTracer_Tests Math/Vector3.cpp)

target_link_libraries(RayTracer_Tests PRIVATE Catch2::Catch2WithMain RayTracer_Headers)

add_test(NAME RayTracer_Tests COMMAND RayTracer_Tests)
