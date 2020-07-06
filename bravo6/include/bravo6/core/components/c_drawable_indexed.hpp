#pragma once

#include <cstdint>

namespace bravo6 {
namespace components {

struct c_drawable_indexed
{
	std::uint32_t vertex_array_object_;
	std::uint32_t index_count_;
};

} // namespace components
} // namespace bravo6