#pragma once

#include <memory>
#include <string>
#include <vector>

#include "bravo6/core/components/c_shader.hpp"
#include "bravo6/core/components/c_texture.hpp"

namespace bravo6 {

enum class SHADER_SOURCE {
	FILE_SOURCE,
	STRING_SOURCE
};

class constructor_helper {
	using shader_component_t  = bravo6::components::c_shader;
	using texture_component_t = bravo6::components::c_texture;
public:
	
	constructor_helper();

	~constructor_helper();

	shader_component_t create_shader_component(SHADER_SOURCE shader_cource, const std::string& vertex_source, const std::string& fragment_source) noexcept;

	texture_component_t create_texture_component(const std::string& texture_path);

private:
	std::vector<std::uint32_t> shader_programs_{};
	std::vector<std::uint32_t> textures_{};
};

} // namespace bravo6