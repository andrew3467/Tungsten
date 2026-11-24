

find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)



file(GLOB_RECURSE SRC CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS *.h)


add_library(
        TungstenEngine
        STATIC
        ${SRC}
        ${HEADERS}
)

target_link_libraries(
        TungstenEngine
        PUBLIC
        spdlog::spdlog
        ImGui
        PRIVATE
        glad::glad
        glfw
        glm::glm
        stb
)

target_precompile_headers(
        TungstenEngine
        PRIVATE
        tungstenpch.h
)

target_include_directories(
        TungstenEngine
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/external/imgui
        PRIVATE
        ${CMAKE_SOURCE_DIR}/external/stb
)

target_compile_definitions(
        TungstenEngine
        PUBLIC

        GLFW_INCLUDE_NONE
        ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets"
)