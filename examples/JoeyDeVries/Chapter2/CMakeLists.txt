# prepare shader files for chapter examples
file(COPY
        shader/colors.vs
        shader/colors.fs
        shader/light_cube.fs
        shader/basic_lighting.vs
        shader/basic_lighting.fs
        shader/basic_lighting_specular.vs
        shader/basic_lighting_specular.fs
        shader/exercise-2.fs
        shader/exercise-3.vs
        shader/exercise-3.fs
        shader/exercise-4.vs
        shader/exercise-4.fs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

add_executable(joey-ex-1-1-colors ex-1-1-colors.cpp)
target_link_libraries(joey-ex-1-1-colors PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-2-1-diffuse ex-2-1-diffuse.cpp)
target_link_libraries(joey-ex-2-1-diffuse PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-2-2-specular ex-2-2-specular.cpp)
target_link_libraries(joey-ex-2-2-specular PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-2-3-lighting-exercise-1 ex-2-3-lighting-exercise-1.cpp)
target_link_libraries(joey-ex-2-3-lighting-exercise-1 PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-2-4-lighting-exercise-2 ex-2-4-lighting-exercise-2.cpp)
target_link_libraries(joey-ex-2-4-lighting-exercise-2 PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-2-5-lighting-exercise-3 ex-2-5-lighting-exercise-3.cpp)
target_link_libraries(joey-ex-2-5-lighting-exercise-3 PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-2-6-lighting-exercise-4 ex-2-6-lighting-exercise-4.cpp)
target_link_libraries(joey-ex-2-6-lighting-exercise-4 PRIVATE Mn::Engine PRIVATE Mn::Joey)
