#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

namespace bravo6 {
namespace components {

struct c_model_view_projection
{
	glm::mat4 model_		= glm::mat4(1.0f);;
	glm::mat4 view_			= glm::mat4(1.0f);;
	glm::mat4 projection_	= glm::mat4(1.0f);;
};

} // namespace components
} // namespace bravo6