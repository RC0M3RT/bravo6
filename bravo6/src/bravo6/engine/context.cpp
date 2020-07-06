#include "bravo6/engine/context.hpp"
#include "bravo6/core/window.hpp"

#include <GLFW/glfw3.h>

namespace bravo6 {

context::context()
    : window_{ std::make_unique<bravo6::window>() }
{
    window_->init();
}

context::context(context&& other) noexcept
    : window_{ std::move(other.window_) }
{
    window_->init();
}

bravo6::window* context::get_window() const
{
    return window_.get();
}

bool context::active() const
{
    return !glfwWindowShouldClose(window_->gl_window_);
}

} // namespace bravo6