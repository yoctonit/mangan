# prepare shader files for chapter examples
file(COPY
        shader/depth_testing.vs
        shader/depth_testing.fs
        shader/depth_testing_view.vs
        shader/depth_testing_view.fs
        shader/stencil_testing.vs
        shader/stencil_testing.fs
        shader/stencil_single_color.vs
        shader/stencil_single_color.fs
        shader/blending.vs
        shader/blending_discard.fs
        shader/blending.fs
        shader/framebuffers.vs
        shader/framebuffers.fs
        shader/framebuffers_screen.vs
        shader/framebuffers_screen.fs
        shader/cubemaps.vs
        shader/cubemaps.fs
        shader/skybox.vs
        shader/skybox.fs
        shader/cubemaps_environment.vs
        shader/cubemaps_environment.fs
        shader/advanced_glsl.vs
        shader/red.fs
        shader/green.fs
        shader/blue.fs
        shader/yellow.fs
        shader/geometry_shader.vs
        shader/geometry_shader.gs
        shader/geometry_shader.fs
        shader/geometry_shader_2.vs
        shader/geometry_shader_2.gs
        shader/geometry_shader_2.fs
        shader/gs_default.vs
        shader/gs_default.fs
        shader/normal_visualization.vs
        shader/normal_visualization.gs
        shader/normal_visualization.fs
        shader/instancing.vs
        shader/instancing.fs
        shader/instancing_mvp.vs
        shader/instancing_mvp.fs
        shader/instancing_mvp_asteroids.vs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shader)

file(COPY
        ../images/container.jpg
        ../images/grass.png
        ../images/marble.jpg
        ../images/metal.png
        ../images/window.png
        ../images/skybox/back.jpg
        ../images/skybox/bottom.jpg
        ../images/skybox/front.jpg
        ../images/skybox/left.jpg
        ../images/skybox/right.jpg
        ../images/skybox/top.jpg
        ../images/container2.png
        ../images/sandy_planet.png
        ../images/rock.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

add_executable(joey-ex-1-1-depth-testing ex-1-1-depth-testing.cpp)
target_link_libraries(joey-ex-1-1-depth-testing PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-1-2-depth-testing-view ex-1-2-depth-testing-view.cpp)
target_link_libraries(joey-ex-1-2-depth-testing-view PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-2-1-stencil-testing ex-2-1-stencil-testing.cpp)
target_link_libraries(joey-ex-2-1-stencil-testing PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-3-1-blending-discard ex-3-1-blending-discard.cpp)
target_link_libraries(joey-ex-3-1-blending-discard PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-3-2-blending ex-3-2-blending.cpp)
target_link_libraries(joey-ex-3-2-blending PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-5-1-framebuffers ex-5-1-framebuffers.cpp)
target_link_libraries(joey-ex-5-1-framebuffers PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-5-2-framebuffers-exercise-1 ex-5-2-framebuffers-exercise-1.cpp)
target_link_libraries(joey-ex-5-2-framebuffers-exercise-1 PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-6-1-cubemaps-skybox ex-6-1-cubemaps-skybox.cpp)
target_link_libraries(joey-ex-6-1-cubemaps-skybox PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-6-2-cubemaps-environment-mapping ex-6-2-cubemaps-environment-mapping.cpp)
target_link_libraries(joey-ex-6-2-cubemaps-environment-mapping PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-8-1-glsl-ubo ex-8-1-glsl-ubo.cpp)
target_link_libraries(joey-ex-8-1-glsl-ubo PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-9-1-geometry-shader-houses ex-9-1-geometry-shader-houses.cpp)
target_link_libraries(joey-ex-9-1-geometry-shader-houses PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-9-2-geometry-shader-exploding ex-9-2-geometry-shader-exploding.cpp)
target_link_libraries(joey-ex-9-2-geometry-shader-exploding PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-9-3-normal-visualization ex-9-3-normal-visualization.cpp)
target_link_libraries(joey-ex-9-3-normal-visualization PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-10-1-instancing ex-10-1-instancing.cpp)
target_link_libraries(joey-ex-10-1-instancing PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-10-2-asteroids ex-10-2-asteroids.cpp)
target_link_libraries(joey-ex-10-2-asteroids PRIVATE Mn::GL PRIVATE Mn::Joey)

add_executable(joey-ex-10-3-asteroids-instancing ex-10-3-asteroids-instancing.cpp)
target_link_libraries(joey-ex-10-3-asteroids-instancing PRIVATE Mn::GL PRIVATE Mn::Joey)
