cmake_minimum_required(VERSION 3.16)
project(timber)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Tell SFML to use system FreeType instead of fetching its own
set(SFML_USE_SYSTEM_DEPS ON)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0
)
FetchContent_MakeAvailable(SFML)

add_executable(timber MACOSX_BUNDLE src/timber.cpp)

target_link_libraries(timber PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    "-framework Cocoa"
)

set_target_properties(timber PROPERTIES
    MACOSX_BUNDLE TRUE
    BUILD_RPATH "${CMAKE_BINARY_DIR}/_deps/sfml-build/lib"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_command(TARGET timber POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/src/graphics/background.png
    ${CMAKE_SOURCE_DIR}/background.png  # <-- copies to project root
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/src/graphics/background.png
    $<TARGET_FILE_DIR:timber>/background.png  # <-- copies inside .app
)







































































