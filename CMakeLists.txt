cmake_minimum_required(VERSION 3.20)
project(CPPFeature CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add one line per feature folder
add_subdirectory(span)
add_subdirectory(enable_shared_from_this)
add_subdirectory(concepts)
add_subdirectory(decltype)
add_subdirectory(sfinae)
