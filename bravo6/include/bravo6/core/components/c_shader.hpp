#pragma once

#include <cstdint>
#include <vector>

#include "c_texture.hpp"

namespace bravo6 {
namespace components {

struct c_shader
{
	std::uint32_t shader_program_id_;

	int uniform_projection_location_;
	int uniform_model_location_;
	int uniform_view_location_;

	bool is_valid_{};

	std::vector<c_texture> textures_;
};

} // namespace components
} // namespace bravo6