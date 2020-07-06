#pragma once

#include <cstdint>

namespace bravo6 {
namespace components {

struct c_texture
{
	std::uint32_t texture_id_;
	std::uint32_t texture_slot_;
	int width_;
	int height_;
	int bit_depth_;
	bool loaded_;
};

} // namespace components
} // namespace bravo6