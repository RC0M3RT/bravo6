#include "bravo6/core/shader_helper.hpp"
#include "bravo6/logging/logging.hpp"
#include "bravo6_config.hpp"

#include <GL\glew.h>

#include <fstream>
#include <iostream>
#include <sstream>

#if GLM_VERSION == 998
#pragma warning(push)
#pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#include <glm/gtc/type_ptr.hpp>
#pragma warning( pop )
#endif // GLM_VERSION == 998

namespace bravo6 {

shader_helper::shader_component_t shader_helper::from_file(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
	auto vertex_content = get_file_contents(vertex_shader_path);
	auto fragment_content = get_file_contents(fragment_shader_path);

	if (false == vertex_content.empty() && false == fragment_content.empty()) {
		return from_string(vertex_content, fragment_content);
	}
	else{
		bravo6::components::c_shader shader_component;
		shader_component.is_valid_ = false;
		return shader_component;
	}
}

shader_helper::shader_component_t shader_helper::from_string(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
{
	auto shader_program_id = glCreateProgram();

	bravo6::components::c_shader shader_component;

	std::uint32_t vertex_shader_id;
	std::uint32_t fragment_shader_id;
	if ( create_shader(vertex_shader_source.c_str(), GL_VERTEX_SHADER, vertex_shader_id) && 
		 create_shader(fragment_shader_source.c_str(), GL_FRAGMENT_SHADER, fragment_shader_id) ) {

		glAttachShader(shader_program_id, vertex_shader_id);
		glAttachShader(shader_program_id, fragment_shader_id);

		glLinkProgram(shader_program_id);
		glValidateProgram(shader_program_id);
		
		shader_component.shader_program_id_ = shader_program_id;
		shader_component.uniform_model_location_ = glGetUniformLocation(shader_program_id, "u_Model");
		shader_component.uniform_view_location_ = glGetUniformLocation(shader_program_id, "u_View");
		shader_component.uniform_projection_location_ = glGetUniformLocation(shader_program_id, "u_Projection");
		
		shader_component.is_valid_ = true;

		return shader_component;
	}

	shader_component.is_valid_ = false;
	return shader_component;
}

std::string shader_helper::get_file_contents(const std::string& file_path)
{
	std::ifstream fs_(file_path, std::ios::in);

	if (false == fs_.is_open()) {
		B6_WARN("Failed to read file: {}", file_path)
		return "";
	}

	std::string file_content = std::string((std::istreambuf_iterator<char>(fs_)), (std::istreambuf_iterator<char>()));

	fs_.close();

	return file_content;
}

bool shader_helper::create_shader(const char* shader_source, std::uint32_t shader_type, std::uint32_t& shader_id)
{
	shader_id = glCreateShader(shader_type);

	glShaderSource(shader_id, 1, &shader_source, nullptr);
	glCompileShader(shader_id);

	int result_;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result_);

	if (result_ == GL_FALSE) {

		int len_;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len_);

		char* msg_ = (char*)_malloca(len_ * sizeof(char));
		glGetShaderInfoLog(shader_id, len_, &len_, msg_);

		B6_WARN("-------------------------")
		B6_WARN("Could not compile shader:\n{}", shader_source)
		B6_WARN("-------------------------")

		glDeleteShader(shader_id);

		return false;
	}

	return true;
}

} // namespace bravo6