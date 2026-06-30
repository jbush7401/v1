cmake_minimum_required(VERSION 3.21)
project(engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Pull SDL3 straight from the source and build it as part of the project
include(FetchContent)
FetchContent_Declare(
	SDL3
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-3.4.10
)
FetchContent_MakeAvailable(SDL3)

add_executable(engine
	src/main.cpp
)
target_link_libraries(engine PRIVATE SDL3::SDL3)

#SDL3 builds as a DLL. After linking, copy whatever runtime DLLs are needed to the output directory so that the executable can run.
add_custom_command(TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:engine> $<TARGET_FILE_DIR:engine>
    COMMAND_EXPAND_LISTS
)