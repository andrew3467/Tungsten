file(GLOB_RECURSE SRC CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS *.h)

add_executable(
        TungstenEditor
        ${SRC}
        ${HEADERS}
)

target_link_libraries(
        TungstenEditor
        PRIVATE
        TungstenEngine
)

target_precompile_headers(
        TungstenEditor
        PRIVATE
        ../Tungsten/tungstenpch.h
)

target_include_directories(
        TungstenEditor
        PRIVATE
        ${CMAKE_SOURCE_DIR}
)