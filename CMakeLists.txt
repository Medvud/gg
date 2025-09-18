cmake_minimum_required(VERSION 3.10)
project(tp_rk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(state_lib)
add_subdirectory(HasQuarterState_lib)
add_subdirectory(NoQuarterState_lib)
add_subdirectory(gumballmachine_lib)
add_subdirectory(soldoutstate_lib)
add_subdirectory(soldstate_lib)
add_subdirectory(winnerstate_lib)

add_executable(tp_rk_exec main.cpp)

target_link_libraries(tp_rk_exec
    PRIVATE
        state_lib
        HasQuarterState_lib
        NoQuarterState_lib
        gumballmachine_lib
        soldoutstate_lib
        soldstate_lib
        winnerstate_lib
)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test tests/test.cpp)
add_tests(test)

include(CPack)