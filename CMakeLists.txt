project(sig-segv-test)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3 -Wall -Wextra -Werror -pedantic-errors -fnon-call-exceptions")

add_executable(${PROJECT_NAME}
    main.cpp
    sigSeg.cpp
)

enable_testing()
add_test(NAME ${PROJECT_NAME}
         COMMAND ${PROJECT_NAME})
