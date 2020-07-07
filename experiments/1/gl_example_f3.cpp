
// It is advised to first do scaling operations, then rotations and lastly translations

#include <stdio.h>

#include <imgui.h>

#include <bravo6/logging/logging.hpp>

#include <GL/glew.h>
// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <bravo6/engine/engine.hpp>
#include <bravo6/engine/context.hpp>
#include <bravo6/core/window.hpp>
#include <bravo6/core/shader_helper.hpp>
#include <bravo6/engine/ec_manager.hpp>
#include <bravo6/core/resource_helper.hpp>
#include <bravo6/core/components/c_model_view_projection.hpp>
#include <yaecs.hpp>

#if GLM_VERSION == 998
#pragma warning(push)
#pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#include <glm/gtc/type_ptr.hpp>
#pragma warning( pop )
#endif // GLM_VERSION == 998

#include "test_system.hpp"

void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int, char**)
{
    B6_INFO("App started")

    auto engine_ = bravo6::engine();

    // auto* context_ = engine_.get_context();
    
    engine_.register_system(new test::test_system_1{});

    engine_.exec();

    return 0;
}
