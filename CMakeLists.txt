cmake_minimum_required(VERSION 3.27)
project(dummy)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  misc-base
  GIT_REPOSITORY https://github.com/naemnamenmea/misc-base.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(misc-base)

set(CURRENT_TARGET my_testing_tools)

file(GLOB SOURCE_FILES
    public/*.hpp
    public/*.h
    src/*.cpp
    *.cpp
    *.h
    *.hpp
)

add_library(${CURRENT_TARGET} STATIC ${SOURCE_FILES})
set_target_properties(${CURRENT_TARGET} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${CURRENT_TARGET} PUBLIC misc-base)

target_include_directories(${CURRENT_TARGET} PUBLIC public)
