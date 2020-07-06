#include "bravo6/engine/engine.hpp"
#include "bravo6/logging/logging.hpp"
#include "bravo6/engine/context.hpp"
#include "bravo6/engine/ec_manager.hpp"
#include "bravo6/core/constructor_helper.hpp"

#include "bravo6/systems/render_system.hpp"

#include <GLFW/glfw3.h>

namespace bravo6 {

engine::engine()
    : context_{ new ctx_t() }
    , ec_manager_{ new bravo6::ec_manager() }
    , render_system_{ new bravo6::render_system() }
    , ctor_helper_{ new bravo6::constructor_helper() }
{

}

engine::engine(ctx_t&& ctx)
    : context_{ new ctx_t(std::move(ctx)) }
    , ec_manager_{ new bravo6::ec_manager() }
    , render_system_{ new bravo6::render_system() }
    , ctor_helper_{ new bravo6::constructor_helper() }
{
}

engine::~engine()
{
    for (auto* s : systems_) {
        if (s) {
            delete s;
        }
    }

    systems_.clear();

    delete ec_manager_;
    delete render_system_;
    delete ctor_helper_;
    delete context_;
}

engine::ctx_t* engine::get_context() const
{
    return context_;
}

ec_manager* engine::get_ec_manager()
{
    return ec_manager_;
}

void engine::register_system(bravo6::system_base* s)
{
    if (s) {
        auto* ss = systems_.emplace_back(std::move(s));
        ss->on_load(ec_manager_, context_, ctor_helper_);
    }
    else {
        B6_WARN("Cannot register nullptr system!");
    }
}

void engine::exec()
{
    double delta_time_{ 0 };
    double last_time_{ 0 };

    while (context_->active())
    {
        double now = glfwGetTime();
        delta_time_ = now - last_time_;
        last_time_  = now;

        for (auto* system_ : systems_) {
            system_->update(static_cast<float>(delta_time_), ec_manager_);
        }

        render_system_->render(ec_manager_, context_);
    }
}


} // namespace bravo6