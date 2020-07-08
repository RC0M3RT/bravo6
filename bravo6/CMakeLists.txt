project(bravo6 CXX)

add_library(bravo6
        "${CMAKE_BINARY_DIR}/config/bravo6_config.hpp"
        
        "include/bravo6/logging/logging.hpp"
        "include/bravo6/core/window.hpp"
        "include/bravo6/engine/engine.hpp"
        "include/bravo6/engine/context.hpp"
        "include/bravo6/engine/ec_manager.hpp"
        "include/bravo6/imgui/imgui_impl_glfw.h"
        "include/bravo6/imgui/imgui_impl_opengl3.h"

        "include/bravo6/core/components/c_shader.hpp"

        "include/yaecs.hpp"
        "include/yaecs/entity.hpp"
        "include/yaecs/ec_traits.hpp"
        "include/yaecs/ec_engine.hpp"
        "include/yaecs/component_storage.hpp"
        "include/yaecs/signature_storage.hpp"
        "include/mpl/mpl.hpp"

        "src/bravo6/logging/logging.cpp"
        "src/bravo6/core/window.cpp"
        "src/bravo6/engine/engine.cpp"
        "src/bravo6/engine/context.cpp"
        
        "src/bravo6/imgui/imgui_impl_glfw.cpp"
        "src/bravo6/imgui/imgui_impl_opengl3.cpp"

        "include/bravo6/core/shader_helper.hpp" 
        "src/bravo6/core/shader_helper.cpp" 
        "include/bravo6/core/components/c_drawable.hpp"
        "include/bravo6/systems/render_system.hpp" 
        "src/bravo6/systems/render_system.cpp" 
        "include/bravo6/3rdparty/stb_image.h" 
         
         
        "include/bravo6/core/components/c_texture.hpp" 
        "include/bravo6/core/resource_helper.hpp" 
        "include/bravo6/core/components/c_model_view_projection.hpp" 
        "include/bravo6/systems/system_base.hpp"  
        "include/bravo6/core/components/c_drawable_indexed.hpp" 
        "include/bravo6/core/constructor_helper.hpp" 
        "src/bravo6/core/constructor_helper.cpp" 
        "include/bravo6/core/texture_helper.hpp" 
        "src/bravo6/core/texture_helper.cpp" 
        "include/bravo6/engine/input_manager.hpp" 
        "src/bravo6/engine/input_manager.cpp" 
        "include/bravo6/types/observer_ptr.hpp")

target_include_directories(bravo6 PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include" "${CMAKE_BINARY_DIR}/config/")

target_link_libraries(bravo6 PUBLIC 
    project_warnings 
    project_options 
    CONAN_PKG::imgui 
    CONAN_PKG::glfw 
    CONAN_PKG::glew 
    CONAN_PKG::glm
    CONAN_PKG::fmt 
    CONAN_PKG::spdlog
)
