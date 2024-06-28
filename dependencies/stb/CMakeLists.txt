add_library(stb_lib INTERFACE)
target_include_directories(stb_lib INTERFACE include)
add_library(nothings::stb ALIAS stb_lib)

#add_library(header_only_lib INTERFACE)
#target_include_directories(header_only_lib INTERFACE path_to_header_dir)
#target_link_libraries(your_app_or_lib PRIVATE header_only_lib)