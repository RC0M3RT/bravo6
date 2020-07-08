#include "bravo6/engine/input_manager.hpp"
#include "bravo6/logging/logging.hpp"

#include <GLFW/glfw3.h>

namespace bravo6 {

void input_manager::key_callback(GLFWwindow* window, int key, int scancode, int action , int mods)
{
	decltype(auto) im_ = reinterpret_cast<input_manager*>(glfwGetWindowUserPointer(window));
	if (im_){
		im_->key_callback_(key, scancode, action, mods);
	}
	else{
		B6_CRIT("Cannot get window user pointer")
	}
}

void input_manager::key_callback_(int key, int scancode [[maybe_unused]], int action, int mods [[maybe_unused]] )
{
	if (action == GLFW_PRESS) {
		B6_TRACE("Key Pressed: {}", key)
	}
	if (action == GLFW_RELEASE) {
		B6_TRACE("Key Released: {}", key)
	}
}

} // namespace bravo6