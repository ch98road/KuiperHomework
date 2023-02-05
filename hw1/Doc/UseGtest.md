

### how 2 use gtest(use with out install)
```cpp
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
```



### how 2 install && use gtest by cmake



#### install
```cpp
    git clone https://github.com/google/googletest.git -b v1.13.0
    cd googletest        # Main directory of the cloned repository.
    mkdir build          # Create a directory to hold the build output.
    cd build
    cmake ..             # Generate native build scripts for GoogleTest.
                        # build only GoogleTest : cmake .. -DBUILD_GMOCK=OFF   
    sudo make install
```

#### use
- CMakeLists.txt:
```cpp
    find_package(GTest REQUIRED)
    find_package(glog 0.6.0 REQUIRED)
    aux_source_directory(../test DIR_TEST)
    set(link_lib  glog::glog gtest gtest_main pthread)
    add_executable(test_kuiper_course ${DIR_TEST})
    link_directories(/usr/local/lib/)
    target_link_libraries(test_kuiper_course ${link_lib})

```