#include "bravo6/core/constructor_helper.hpp"
#include "bravo6/core/shader_helper.hpp"
#include "bravo6/core/texture_helper.hpp"

#include <GL\glew.h>

namespace bravo6 {

constructor_helper::constructor_helper()
{
}

constructor_helper::~constructor_helper() 
{
	for (auto spi : shader_programs_) {
		glDeleteProgram(spi);
	}

	for (auto ti : textures_) {
		glDeleteTextures(1, &ti);
	}

	shader_programs_.clear();
	textures_.clear();
}

constructor_helper::shader_component_t constructor_helper::create_shader_component(SHADER_SOURCE shader_cource, const std::string& vertex_source, const std::string& fragment_source) noexcept
{
	shader_component_t shader_component;
	if (shader_cource == SHADER_SOURCE::FILE_SOURCE) {
		shader_component = shader_helper::from_file(vertex_source, fragment_source);
	}
	else {
		shader_component = shader_helper::from_string(vertex_source, fragment_source);
	}

	if (shader_component.is_valid_) {
		shader_programs_.push_back(shader_component.shader_program_id_);
	}

	return shader_component;
}

constructor_helper::texture_component_t constructor_helper::create_texture_component(const std::string& texture_path)
{
	auto texture_component = texture_helper::from_file(texture_path);
	if (texture_component.loaded_) {
		textures_.push_back(texture_component.texture_id_);
	}

	return texture_component;
}

} // namespace bravo6