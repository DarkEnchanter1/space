cmake_minimum_required (VERSION 2.6)
project (Space)
# The version number.
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(PhysicsSourceList "physics.cpp" "physics.hpp")
set(RenderSourceList 
        "rendering/renderer.cpp"      "rendering/renderer.hpp"
        "rendering/utils/shader.cpp" "rendering/utils/shader.hpp"
        "rendering/utils/text2D.cpp" "rendering/utils/text2D.hpp"
        "rendering/utils/texture.cpp" "rendering/utils/texture.hpp")
set(CommonSourceList
        "common/controls.cpp" "common/controls.hpp"
        "common/delta.cpp" "common/delta.hpp"
        "common/primitives.hpp")
set (MainSourceList
        "space.cpp")
set (Space_VERSION_MAJOR 1)
set (Space_VERSION_MINOR 0)
# Add the executable
add_executable(Space ${PhysicsSourceList} ${RenderSourceList} ${CommonSourceList} ${MainSourceList})
# Gets and adds OpenGL to the project.
find_package (OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries ( Space ${OPENGL_LIBRARIES})
# Adds GLEW to the project
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(Space ${GLEW_LIBRARIES})
endif()
find_package(glfw3 REQUIRED)
if (glfw3_FOUND)
    include_directories("/usr/include/GLFW")
    target_link_libraries(Space "/usr/lib/libglfw.so")
    add_definitions(${glfw3_DEFINITIONS})
endif()
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Space Threads::Threads)