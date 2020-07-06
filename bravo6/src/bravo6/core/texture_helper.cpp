#include "bravo6/core/texture_helper.hpp"
#include "bravo6/logging/logging.hpp"
#include <bravo6/core/resource_helper.hpp>

#include <GL\glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "bravo6/3rdparty/stb_image.h"

namespace bravo6 {

texture_helper::texture_component_t texture_helper::from_file(const std::string& texture_path)
{
	texture_component_t texture_component;

	auto full_path_ = bravo6::resource_helper::get_resource_path(texture_path);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* texture_data_ = stbi_load(full_path_.c_str(), &texture_component.width_, &texture_component.height_, &texture_component.bit_depth_, 0);

	if (nullptr == texture_data_) {
		B6_WARN("Could not load texture: {}", texture_path)
		texture_component.loaded_ = false;
	}
	else {

		glGenTextures(1, &texture_component.texture_id_);
		glBindTexture(GL_TEXTURE_2D, texture_component.texture_id_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_component.width_, texture_component.height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data_);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture_component.loaded_ = true;

		stbi_image_free(texture_data_);
	}

	return texture_component;
}

} // namespace bravo6