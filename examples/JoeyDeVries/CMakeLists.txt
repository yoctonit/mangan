add_library(joey_lib
        lib/Camera.cpp)
target_link_libraries(joey_lib PRIVATE glm::glm)
target_include_directories(joey_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_library(Mn::Joey ALIAS joey_lib)

#add_subdirectory(Chapter1)
#add_subdirectory(Chapter2)
add_subdirectory(Chapter4)
