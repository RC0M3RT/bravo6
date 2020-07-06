
add_executable(folder3_gl_ex gl_example_f3.cpp "test_system.hpp" "test_system.cpp")

target_link_libraries(folder3_gl_ex PRIVATE project_warnings project_options 
											CONAN_PKG::glfw 
											CONAN_PKG::glew 
											CONAN_PKG::glm 
											CONAN_PKG::imgui 
											bravo6 
											)
