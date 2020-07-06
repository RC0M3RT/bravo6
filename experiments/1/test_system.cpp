#include "test_system.hpp"

#include <bravo6/engine/ec_manager.hpp>
#include <bravo6/logging/logging.hpp>
#include <bravo6/core/shader_helper.hpp>
#include <bravo6/core/resource_helper.hpp>
#include <bravo6/engine/context.hpp>
#include <bravo6/core/constructor_helper.hpp>

#include <GL/glew.h>
// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <yaecs.hpp>

#if GLM_VERSION == 998
#pragma warning(push)
#pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#include <glm/gtc/type_ptr.hpp>
#pragma warning( pop )
#endif // GLM_VERSION == 998

std::string vertex_shader_source =
R"(
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_Projection;
uniform mat4 u_View;

void main(){
    // gl_Position = projection * view * model * vec4(position, 1.0);  ---> this has to be like this
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
    v_TexCoord = texCoord;
}
)";

std::string fragment_shader_source =
R"(
#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color; // we can set this from cpp
uniform sampler2D u_Texture;

void main(){

    vec4 texColor = texture(u_Texture, v_TexCoord);

    color = texColor; //  * vec4(1.0, 0.0, 0.0, 1.0);
}
)";

namespace test {

test_system_1::test_system_1()
{
}

test_system_1::~test_system_1()
{
}

void test_system_1::on_load(bravo6::ec_manager* ecm, bravo6::context* ctx, bravo6::constructor_helper* cth)
{
    B6_TRACE("test_system_1::on_load()");

    auto shader_component_ = cth->create_shader_component(bravo6::SHADER_SOURCE::STRING_SOURCE, vertex_shader_source, fragment_shader_source);
    auto texture_component = cth->create_texture_component("textures/awesomeface.png");

    if (shader_component_.is_valid_) {
        B6_INFO("test_system_1 shader_component_ is loaded and valid");
    }

    if (texture_component.loaded_) {
        B6_INFO("test_system_1 texture_component is loaded and usable")
    }

    auto default_projection_matrix_ = glm::perspective(glm::radians(45.0f), ctx->get_window()->aspect(), 0.1f, 100.0f);

    float vertices[] = {
        //   x      y     z       u     v
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    texture_component.texture_slot_ = 0;

    auto entity_rectangle_ = ecm->create_entity();

    shader_component_.textures_.push_back(texture_component);

    ecm->add_component<bravo6::components::c_shader>(entity_rectangle_, shader_component_);

    auto d = bravo6::components::c_drawable{};
    d.vertex_array_object_ = VAO;
    d.vertex_count_ = 36;

    ecm->add_component<bravo6::components::c_drawable>(entity_rectangle_, d);

    auto mvp_c = bravo6::components::c_model_view_projection{};

    mvp_c.projection_ = default_projection_matrix_;
    mvp_c.view_ = glm::translate(mvp_c.view_, glm::vec3(0.0f, 0.0f, -3.0f));

    // mvp_c.model_ = glm::rotate(mvp_c.model_, 30.0f, glm::vec3(0.5f, 1.0f, 0.0f));

    glUseProgram(shader_component_.shader_program_id_);
    glUniformMatrix4fv(shader_component_.uniform_model_location_, 1, GL_FALSE, glm::value_ptr(mvp_c.model_));
    glUniformMatrix4fv(shader_component_.uniform_view_location_, 1, GL_FALSE, glm::value_ptr(mvp_c.view_));
    glUniformMatrix4fv(shader_component_.uniform_projection_location_, 1, GL_FALSE, glm::value_ptr(mvp_c.projection_));

    glUniform1i(glGetUniformLocation(shader_component_.shader_program_id_, "u_Texture"), 0);

    ecm->add_component<bravo6::components::c_model_view_projection>(entity_rectangle_, mvp_c);
}

void test_system_1::update(float delta_time, bravo6::ec_manager* ecm)
{
    using namespace bravo6::components;

    ecm->for_matching_entities<c_shader, c_model_view_projection>([delta_time](c_shader& s, c_model_view_projection& mvp_c) {

        mvp_c.model_ = glm::rotate(mvp_c.model_, glm::radians(100.0f * delta_time), glm::vec3(1.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(s.uniform_model_location_, 1, GL_FALSE, glm::value_ptr(mvp_c.model_));

    });
}

}