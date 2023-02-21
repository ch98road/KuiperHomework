cmake_minimum_required(VERSION 3.16)
project(test_kuiper)

set(CMAKE_CXX_STANDARD 17)

find_package(glog 0.6.0 REQUIRED)
find_package(GTest REQUIRED)

include_directories(../include)
aux_source_directory(../source/data DATA)
aux_source_directory(../source/layer LAYER)
aux_source_directory(../source/ops OP)
aux_source_directory(../source/factory FACTORY)

set(test_link_lib glog::glog gtest gtest_main pthread)
set(test_link_math_lib armadillo blas lapack)
link_directories(/usr/local/lib/)

enable_testing()

# test_tensor
# add_executable(test_tensor testTensor.cc ${DATA})
# target_link_libraries(test_tensor ${test_link_lib} ${test_link_math_lib})
# gtest_discover_tests(test_tensor)

# # test_load_data
# add_executable(test_load_data testLoadData.cc ${DATA})
# target_link_libraries(test_load_data ${test_link_lib} ${test_link_math_lib})
# gtest_discover_tests(test_load_data)


# # test_relu
# add_executable(test_relu testRelu.cc ${DATA} ${LAYER} ${OP} ${FACTORY})
# target_link_libraries(test_relu ${test_link_lib} ${test_link_math_lib})
# gtest_discover_tests(test_relu)


# # test_sigmoid
# add_executable(test_sigmoid testSigmoid.cc ${DATA} ${LAYER} ${OP} ${FACTORY})
# target_link_libraries(test_sigmoid ${test_link_lib} ${test_link_math_lib})
# gtest_discover_tests(test_sigmoid)

# test maxpooling
add_executable(test_maxpooling testMaxpooling.cc ${DATA} ${LAYER} ${OP} ${FACTORY})
target_link_libraries(test_maxpooling ${test_link_lib} ${test_link_math_lib})
gtest_discover_tests(test_maxpooling)