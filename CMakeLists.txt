cmake_minimum_required(VERSION 3.14)

project(mpi_tutorial)

set(MPI_EXECUTABLE_SUFFIX ".mpich")
find_package(MPI REQUIRED)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(hello_world hello_world/hello_world.cpp)
target_link_libraries(hello_world ${MPI_C_LIBRARIES})

add_executable(simple_send_recv p2p/simple_send_recv.cpp)
target_link_libraries(simple_send_recv ${MPI_C_LIBRARIES})

install(TARGETS hello_world simple_send_recv
        RUNTIME
        DESTINATION ./)
