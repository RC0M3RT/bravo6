#pragma once

#include <memory>
#include <type_traits>

#include "bravo6/core/window.hpp"

struct GLFWwindow;

namespace bravo6 {

/**
 * @brief 
 * 
 */
class context {
public:

    /**
     * @brief Construct a new default context 
     * 
     */
    context();

    context(context&& other) noexcept;

    bravo6::window* get_window() const;

    bool active() const;

    /**
     * @brief Do something with underlying GLFWwindow*
     * 
     * @param visitor A callable that takes GLFWwindow* as param
     */
    template<typename Visitor>
    void visit_window(Visitor&& visitor)
    {
        if constexpr(std::is_invocable_v<Visitor, GLFWwindow*>){
            visitor(window_->gl_window_);
        }
        else{	
            B6_WARN("Cannot visit window with the given callable");
        }
    }

private:
    std::unique_ptr<bravo6::window> window_{nullptr};
};


} // namespace bravo6