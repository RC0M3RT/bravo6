#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "bravo6/core/components/c_shader.hpp"

namespace bravo6 {

class shader_helper {
	using shader_component_t = bravo6::components::c_shader;

	static shader_component_t from_file(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

	static shader_component_t from_string(const std::string& vertex_shader_source, const std::string& fragment_shader_source);

	static std::string get_file_contents(const std::string& file_path);

	static bool create_shader(const char* shader_source, std::uint32_t shader_type, std::uint32_t& shader_id);

	friend class constructor_helper;
};

} // namespace bravo6