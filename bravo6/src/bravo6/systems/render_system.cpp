#include "bravo6/systems/render_system.hpp"
#include "bravo6/engine/ec_manager.hpp"
#include "bravo6/engine/context.hpp"
#include "bravo6/logging/logging.hpp"

#include "bravo6/core/components/c_drawable.hpp"
#include "bravo6/core/components/c_shader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace bravo6 {

void render_system::render(bravo6::ec_manager* ecm, bravo6::context* ctx)
{
	using namespace bravo6::components;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ecm->for_matching_entities<c_shader, c_drawable>([&](const c_shader& s, const c_drawable& d) {

		for (const auto& texture_ : s.textures_) {
			glActiveTexture(GL_TEXTURE0 + texture_.texture_slot_);
			glBindTexture(GL_TEXTURE_2D, texture_.texture_id_);
		}

		glUseProgram(s.shader_program_id_);
		glBindVertexArray(d.vertex_array_object_);

		glDrawArrays(GL_TRIANGLES, 0, d.vertex_count_);
	});
	
	ecm->for_matching_entities<c_shader, c_drawable_indexed>([&](const c_shader& s, const c_drawable_indexed& d) {

		for (const auto& texture_ : s.textures_) {
			glActiveTexture(GL_TEXTURE0 + texture_.texture_slot_);
			glBindTexture(GL_TEXTURE_2D, texture_.texture_id_);
		}

		glUseProgram(s.shader_program_id_);
		glBindVertexArray(d.vertex_array_object_);

		glDrawElements(GL_TRIANGLES, d.index_count_, GL_UNSIGNED_INT, 0);
	});

	ctx->visit_window([&](GLFWwindow* w) {
		glfwSwapBuffers(w);
	});

	glfwPollEvents();
}

} // namespace bravo6