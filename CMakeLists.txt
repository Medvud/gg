cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STADARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)

project(ChainOfResponsibility)

add_subdirectory(gumballmachine_lib)
add_subdirectory(HasQuarterState_lib)
add_subdirectory(NoQuarterState_lib)
add_subdirectory(soldoutstate_lib)
add_subdirectory(soldstate_lib)
add_subdirectory(state_lib)
add_subdirectory(winnerstate_lib)

add_executable(ChainOfResponsibility main.cpp)
target_link_libraries(ChainOfResponsibility ChainOfResponsibility gumballmachine)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  add_executable(check tests/test.cpp)
  target_link_libraries(check gtest_main ChainOfResponsibility gumballmachine SoldOutState )
  add_test(NAME check COMMAND check)
endif()

include(CPackConfig.cmake)
include(CPack)