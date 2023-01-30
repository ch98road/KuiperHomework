cmake_minimum_required(VERSION 3.16)
project(test_gtest)

set(CMAKE_CXX_STANDARD 17)

find_package(glog 0.6.0 REQUIRED)

include(FetchContent)
FetchContent_Declare(
  gtest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

enable_testing()
include(GoogleTest)
set(link_lib glog::glog gtest_main) 

add_executable(test_gtest testGtest.cc)
target_link_libraries(test_gtest ${link_lib})
gtest_discover_tests(test_gtest)