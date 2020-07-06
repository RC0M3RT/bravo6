#pragma once

#include "components/c_texture.hpp"
#include <string>

namespace bravo6 {

class texture_helper {
	using texture_component_t = bravo6::components::c_texture;

	static texture_component_t from_file(const std::string& texture_path);

	friend class constructor_helper;
};

} // namespace bravo6