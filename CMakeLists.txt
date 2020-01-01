cmake_minimum_required(VERSION 3.15.0)

project(Firebreak VERSION 0.1 DESCRIPTION "Firebreak framework")

include_directories(include /usr/local/include)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14 -O3")
SET(GCC_COVERAGE_LINK_FLAGS "")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
file(GLOB SOURCES "source/*.cpp")

add_library(firebreak SHARED ${SOURCES})

target_link_libraries(firebreak /usr/local/lib/libvulkan.1.1.121.dylib)

set_target_properties(firebreak PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(firebreak PROPERTIES SOVERSION 1)
set_target_properties(firebreak PROPERTIES PUBLIC_HEADER include/firebreak.hpp)
target_include_directories(firebreak PRIVATE include)
target_include_directories(firebreak PRIVATE source)
include(GNUInstallDirs)
install(TARGETS firebreak LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
configure_file(firebreak.pc.in firebreak.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/firebreak.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)