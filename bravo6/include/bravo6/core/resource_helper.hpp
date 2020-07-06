#pragma once

#include <string>
#include <bravo6_config.hpp>

namespace bravo6 {

class resource_helper {
public:

	static std::string get_resource_path(const std::string& relative_resource_path) {
		return {std::string(bravo6::config::resources_directory) + "/" + relative_resource_path};
	}

private:
};

} // namespace bravo6