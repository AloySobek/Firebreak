cmake_minimum_required(VERSION 3.15.0)

project(Firebreak)

include_directories(include /usr/local/include)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14")
SET(GCC_COVERAGE_LINK_FLAGS "")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

file(GLOB SOURCES "source/*.cpp")
add_executable(firebreak ${SOURCES})

target_link_libraries(firebreak PRIVATE /usr/local/lib/libvulkan.1.1.121.dylib)
target_link_libraries(firebreak PRIVATE /Users/vrichese/Workspace/Rus42/MyProjects/WanderingStar/Firebreak/libs/libglfw.3.3.dylib)