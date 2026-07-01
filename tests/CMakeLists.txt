file(GLOB_RECURSE SRC *.cpp)
file(GLOB_RECURSE HEADERS *.h)


add_executable(
        TungstenTests
        ${SRC}
        ${HEADERS}
)

target_link_libraries(
        TungstenTests
        PRIVATE
        Tungsten
)

target_include_directories(
        TungstenTests
        PRIVATE
        ../src
)