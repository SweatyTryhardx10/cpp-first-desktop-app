cmake_minimum_required(VERSION 3.12)
project(myApp VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCE CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB gui_SOURCES CONFIGURE_DEPENDS "imgui/*.cpp")
file(GLOB gui_HEADERS CONFIGURE_DEPENDS "imgui/*.h")

# set(_INCLUDE_DIRS "")
# foreach (_headerFile ${gui_HEADERS})
#     get_filename_component(_dir ${_headerFile} PATH)
#     list (APPEND _INCLUDE_DIRS ${_dir})
# endforeach()
# list(REMOVE_DUPLICATES _INCLUDE_DIRS)

add_executable(myApp ${SOURCE} ${gui_SOURCES} imgui/backends/imgui_impl_win32.cpp imgui/backends/imgui_impl_dx11.cpp)
target_include_directories(myApp PRIVATE imgui/ imgui/backends/)

# Manual include of a select few libraries not automatically found on the system (even though they are there)
target_link_libraries(myApp PRIVATE d3d11 d3dx11 dwmapi d3dcompiler)