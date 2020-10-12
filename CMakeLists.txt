cmake_minimum_required(VERSION 3.17)
project(Raytracer___intro)

set(CMAKE_CXX_STANDARD 11)

include_directories(./include)

add_executable(Raytracer___intro main.cpp src/sphere.cpp src/vec3.cpp src/hittable_list.cpp src/camera.cpp src/lambertian.cpp src/metal.cpp src/dielectric.cpp)