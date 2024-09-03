# prepare shader files for chapter examples
file(COPY
        shader/colors.vs
        shader/colors.fs
        shader/light_cube.fs
        shader/basic_lighting_1.vs
        shader/basic_lighting_1.fs
        shader/basic_lighting_specular.vs
        shader/basic_lighting_specular.fs
        shader/exercise-2.fs
        shader/exercise-3.vs
        shader/exercise-3.fs
        shader/exercise-4.vs
        shader/exercise-4.fs
        shader/materials.fs
        shader/light_cube_exercise_1.fs
        shader/lighting_maps_1.vs
        shader/lighting_maps_1.fs
        shader/lighting_maps_specular.fs
        shader/exercise-4-3.fs
        shader/exercise-4-4.fs
        shader/basic_mvp.vs
        shader/basic_color.fs
        shader/basic_lighting.vs
        shader/basic_lighting.fs
        shader/directional_light.fs
        shader/lighting_maps.vs
        shader/lighting_maps.fs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        ../images/container2.png
        ../images/container2_specular.png
        ../images/container2_specular_colored.png
        ../images/matrix.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

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

add_executable(joey-ex-3-1-materials ex-3-1-materials.cpp)
target_link_libraries(joey-ex-3-1-materials PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-3-2-materials-exercise-1 ex-3-2-materials-exercise-1.cpp)
target_link_libraries(joey-ex-3-2-materials-exercise-1 PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-3-3-materials-exercise-2 ex-3-3-materials-exercise-2.cpp)
target_link_libraries(joey-ex-3-3-materials-exercise-2 PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-4-1-lighting-maps ex-4-1-lighting-maps.cpp)
target_link_libraries(joey-ex-4-1-lighting-maps PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-4-2-lighting-maps-specular ex-4-2-lighting-maps-specular.cpp)
target_link_libraries(joey-ex-4-2-lighting-maps-specular PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-4-3-exercise-2 ex-4-3-exercise-2.cpp)
target_link_libraries(joey-ex-4-3-exercise-2 PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-4-4-exercise-4 ex-4-4-exercise-4.cpp)
target_link_libraries(joey-ex-4-4-exercise-4 PRIVATE Mn::Engine PRIVATE Mn::Joey)

add_executable(joey-ex-5-1-directional-light ex-5-1-directional-light.cpp)
target_link_libraries(joey-ex-5-1-directional-light PRIVATE Mn::Engine PRIVATE Mn::Joey)
