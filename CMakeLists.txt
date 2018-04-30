cmake_minimum_required (VERSION 2.6)
project (Space)
# The version number.
set(PhysicsSourceList "physics.cpp" "physics.hpp")
set(RenderSourceList 
        "rendering/renderer.cpp"      "rendering/renderer.hpp"
        "rendering/utils/shader.cpp" "rendering/utils/shader.hpp"
        "rendering/utils/text2D.cpp" "rendering/utils/text2D.hpp"
        "rendering/utils/shader.cpp" "rendering/utils/shader.hpp")
set (Space_VERSION_MAJOR 1)
set (Space_VERSION_MINOR 0)
# Add the executable
add_executable(Space space.cpp physics.cpp physics.hpp)
# Gets and adds OpenGL to the project.
find_package (OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries ( Space ${OPENGL_LIBRARIES})