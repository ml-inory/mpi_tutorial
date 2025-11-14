cmake_minimum_required(VERSION 3.14)

project(mpi_tutorial)

set(MPI_EXECUTABLE_SUFFIX ".mpich")
find_package(MPI REQUIRED)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(hello_world hello_world/hello_world.cpp)
target_link_libraries(hello_world ${MPI_C_LIBRARIES})

install(TARGETS hello_world
        RUNTIME
        DESTINATION ./)
