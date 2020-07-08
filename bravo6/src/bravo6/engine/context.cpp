#include "bravo6/engine/context.hpp"
#include "bravo6/core/window.hpp"
#include "bravo6/engine/input_manager.hpp"

#include <GLFW/glfw3.h>

namespace bravo6 {

context::context()
    : window_{ std::make_unique<bravo6::window>() }
    , input_manager_{ std::make_unique<bravo6::input_manager>() }
{
    if (window_->init()) {
        setup_input_callbacks();
    }
}

context::~context()
{
}

bravo6::window* context::get_window() const
{
    return window_.get();
}

bool context::active() const
{
    return !glfwWindowShouldClose(window_->gl_window_);
}

void context::setup_input_callbacks()
{
    glfwSetWindowUserPointer(window_->gl_window_, reinterpret_cast<void*>(input_manager_.get()));
    glfwSetKeyCallback(window_->gl_window_, input_manager::key_callback);
}


} // namespace bravo6