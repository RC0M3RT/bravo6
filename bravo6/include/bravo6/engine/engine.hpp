#pragma once

#include "bravo6/systems/system_base.hpp"

#include <vector>

namespace bravo6 {

class context;
class ec_manager;
class render_system;
class constructor_helper;

/**
 * @brief 
 * 
 * @tparam ECSE Entity component system engine
 */
class engine {
    using ctx_t = bravo6::context;
public:

    /**
     * @brief Construct a new engine object with default context
     *
    */
    engine();

    ~engine();

    /**
     * @brief Get the context object
     * 
     * @return ctx_t* 
     */
    ctx_t* get_context() const;

    ec_manager* get_ec_manager();

    void register_system(bravo6::system_base* s);

    /**
     * @brief Starts the engine loop
     */
    void exec();

private:
    ctx_t* context_{ nullptr };
    ec_manager* ec_manager_{ nullptr };
    render_system* render_system_{ nullptr };
    constructor_helper* ctor_helper_{ nullptr };

    std::vector<bravo6::system_base*> systems_{};
};


} // namespace bravo6