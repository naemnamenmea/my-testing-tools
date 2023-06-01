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
target_link_libraries(${CURRENT_TARGET} PUBLIC misc)

target_include_directories(${CURRENT_TARGET} PUBLIC public)