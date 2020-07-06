#include "bravo6/core/window.hpp"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace bravo6{

window::window()
    : width_{800}
    , height_{600}
    , title_{"Test Window"}
    , aspect_{ (float)width_ / (float)height_ }
    , enable_vsync_{true}
{
}

window::window(const window_props& window_properties)
    : width_{window_properties.widht}
    , height_{window_properties.height}
    , title_{window_properties.title}
    , aspect_{ (float)width_ / (float)height_ }
    , enable_vsync_{window_properties.enable_vsync}
{
}

window::~window()
{
	glfwDestroyWindow(gl_window_);
	glfwTerminate();
}

bool window::init()
{
    glfwSetErrorCallback(glfw_error_callback);

	if (false == glfwInit()) {
		B6_CRIT("Could not initialize glfw");
		glfwTerminate();
		return false;
	}

	// Setup GLFW Windows Properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	// Allow forward compatiblity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	gl_window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);

	if (nullptr == gl_window_) {
		B6_CRIT("Could not create a glfw window");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gl_window_);

    if(enable_vsync_){
		B6_TRACE("Enabling vsync")
        glfwSwapInterval(1); // Enable vsync
    }

	// Allow modern extension access
	glewExperimental = GL_TRUE;

	auto result_ = glewInit();
	if (GLEW_OK != result_) {
        B6_CRIT("Could not initialize glew: {}", glewGetErrorString(result_));
		glfwDestroyWindow(gl_window_);
		glfwTerminate();
		return false;
	}

	glEnable(GL_DEPTH_TEST);

    return true;
}

int window::width() const{
    return width_;
}

int window::height() const {
    return height_;
}

float window::aspect() const {
    return aspect_;
}

void window::glfw_error_callback(int error, const char* description)
{
    B6_WARN("GLFW Error {}: {}", error, description);
}

}