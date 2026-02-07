cmake_minimum_required(VERSION 3.10)
project(multirate_controller LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(multirate_controller
    main.cpp
)

add_executable(multirate_controller_test
    test_multirate.cpp
)

add_executable(multirate_controller_position_example
    example_position.cpp
)

add_executable(multirate_controller_runtime
    runtime_main.cpp
)
