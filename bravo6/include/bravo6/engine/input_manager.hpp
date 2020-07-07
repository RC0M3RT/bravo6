#pragma once

struct GLFWwindow;

namespace bravo6 {

class input_manager {
public:

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

} // namespace bravo6