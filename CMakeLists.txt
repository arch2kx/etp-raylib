cmake_minimum_required(VERSION 3.16)
project(EdenTreatyPandemonium)

set(CMAKE_CXX_STANDARD 17)

# Download raylib automatically — no manual install required
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5
    GIT_SHALLOW    TRUE
)
# Suppress raylib's own examples/games from being built
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

add_executable(etp
    src/main.cpp
    src/player.cpp
    src/bullet.cpp
    src/enemy.cpp
    src/boss.cpp
    src/sniper.cpp
    src/game.cpp
)

target_link_libraries(etp raylib)

# Xcode 26 beta moved libc++ headers into the SDK only; the compiler's
# built-in search path (/usr/include/c++/v1) is empty. Point it at the SDK.
if(APPLE)
    execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE APPLE_SDK_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    target_compile_options(etp PRIVATE -isystem ${APPLE_SDK_PATH}/usr/include/c++/v1)
endif()

# Hide the console window on Windows release builds
if(WIN32)
    set_target_properties(etp PROPERTIES WIN32_EXECUTABLE FALSE)
endif()

# Copy assets next to the binary so relative paths work on all platforms
add_custom_command(TARGET etp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:etp>/assets
    COMMENT "Copying assets to build directory"
)
