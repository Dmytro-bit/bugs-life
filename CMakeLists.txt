cmake_minimum_required(VERSION 3.30)
project(bug_life VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# static SFML
add_definitions(-DSFML_STATIC)
set(SFML_DIR "/home/vladikslon/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6 REQUIRED COMPONENTS system window graphics network)

# sources & headers
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.h)

# create your executable (target is just "bug_life")
add_executable(bug_life
        ${SOURCES}
        ${HEADERS}
        src/model/Bishop.cpp
        src/model/Bishop.h
        src/model/Superbug.cpp
        src/model/Superbug.h
)

# includes
target_include_directories(bug_life PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "/home/vladikslon/SFML-2.6.2/include"
)

# link SFML via the imported targets
target_link_libraries(bug_life PRIVATE
        sfml-system sfml-window sfml-graphics
)

