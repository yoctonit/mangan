cmake_minimum_required(VERSION 3.20)
project(OpenGL_Examples VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

##################
# Add dependencies
##################
include(FetchContent)

### GLFW ###
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)

set(GLFW_BUILD_SHARED_LIBRARY OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

### glad extension loading library ###
add_subdirectory(dependencies/glad4.3)

### glm ###
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
        # GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

set(GLM_BUILD_TESTS OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(glm)

### freetype ###
#add_subdirectory(freetype-2.10.1 EXCLUDE_FROM_ALL)

######################
# mangan gl library
######################
add_subdirectory(mnlib)
#add_subdirectory(core)

# add examples
add_subdirectory(examples)
