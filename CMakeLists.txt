cmake_minimum_required(VERSION 3.5.0)
project(web VERSION 0.1.0 LANGUAGES C CXX)
# Include the vcpkg toolchain file from the vcpkg installation
include(../vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Crow CONFIG REQUIRED)
set(TEMPLATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/templates")
add_definitions(-DTEMPLATE_DIR="${TEMPLATE_DIR}")

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Crow::Crow )