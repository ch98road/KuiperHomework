cmake_minimum_required(VERSION 3.16)
project(test_glog)

set(CMAKE_CXX_STANDARD 11)

find_package(glog 0.6.0 REQUIRED)

set(link_lib glog::glog)

add_executable(test_glog testGlog.cc)
target_link_libraries(test_glog ${link_lib})
