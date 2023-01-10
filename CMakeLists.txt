cmake_minimum_required(VERSION 3.15)
project(OpenGL_Examples VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

##################
# Add dependencies
##################
# We have three dependencies?:

# 1. OpenGL
#find_package(OpenGL REQUIRED COMPONENTS OpenGL)

# 2. GLFW
# but don't build the GLFW tests, examples and documentation.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw-3.3.8)

# 3. glad extension loading library
add_subdirectory(deps/glad4.3)

# 4. freetype
#add_subdirectory(freetype-2.10.1 EXCLUDE_FROM_ALL)

######################
# mangan gl library
######################
add_subdirectory(mngl)

# add examples
add_subdirectory(examples)
