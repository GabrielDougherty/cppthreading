cmake_minimum_required(VERSION 3.20)
project(cppthreading)

# Clear any cached compiler settings
unset(CMAKE_C_COMPILER CACHE)
unset(CMAKE_CXX_COMPILER CACHE)

# Only use environment compilers if they are set and valid
if(DEFINED ENV{CC} AND NOT "$ENV{CC}" STREQUAL "")
    set(CMAKE_C_COMPILER $ENV{CC})
endif()

if(DEFINED ENV{CXX} AND NOT "$ENV{CXX}" STREQUAL "")
    set(CMAKE_CXX_COMPILER $ENV{CXX})
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use libc++ instead of libstdc++
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -D_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
endif()

# Remove any hardcoded library paths
set(CMAKE_LIBRARY_PATH "")
set(CMAKE_PREFIX_PATH "")

# Find pthreads
find_package(Threads REQUIRED)

# Main executable
add_executable(threading_practice main.cpp)
target_link_libraries(threading_practice Threads::Threads)

# Example executables
add_executable(mutex_example examples/mutex_example.cpp)
target_link_libraries(mutex_example Threads::Threads)

add_executable(condition_variable_example examples/condition_variable_example.cpp)
target_link_libraries(condition_variable_example Threads::Threads)

add_executable(thread_pool_example examples/thread_pool_example.cpp)
target_link_libraries(thread_pool_example Threads::Threads)

add_executable(atomic_example examples/atomic_example.cpp)
target_link_libraries(atomic_example Threads::Threads)
