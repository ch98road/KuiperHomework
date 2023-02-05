cmake_minimum_required(VERSION 3.16)
project(test_armadillo)

set(CMAKE_CXX_STANDARD 17)

find_package(glog 0.6.0 REQUIRED)

# set(link_lib glog::glog)

# # test_padding
# add_executable(test_padding testPadding.cc)
# target_link_libraries(test_padding ${link_lib})

# # test_fill
# add_executable(test_fill testFill.cc)
# target_link_libraries(test_fill ${link_lib})

enable_testing()
# test_tensor
find_package(GTest REQUIRED)
set(test_link_lib glog::glog gtest gtest_main pthread)
set(test_link_math_lib armadillo blas lapack)

include_directories(../include)
aux_source_directory(../source/data SOURCE)
add_executable(test_tensor testTensor.cc ${SOURCE})
link_directories(/usr/local/lib/)
target_link_libraries(test_tensor ${test_link_lib} ${test_link_math_lib})
gtest_discover_tests(test_tensor)