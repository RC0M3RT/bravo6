#pragma once

#include "yaecs.hpp"

#include "bravo6/core/components/c_shader.hpp"
#include "bravo6/core/components/c_drawable.hpp"
#include "bravo6/core/components/c_model_view_projection.hpp"
#include "bravo6/core/components/c_texture.hpp"
#include "bravo6/core/components/c_drawable_indexed.hpp"

#include <cstdint>

namespace bravo6{

/**
 * @brief Responsible of containing and managing entity component system
*/
class ec_manager {
	/**
	 * @brief All the components will go here
	*/
	using components = yaecs::component_list<
		bravo6::components::c_shader,
		bravo6::components::c_drawable,
		bravo6::components::c_drawable_indexed,
		bravo6::components::c_model_view_projection,
		bravo6::components::c_texture
	>;

	/**
	 * @brief All the signatures will go here
	*/
	using signatures = yaecs::signature_list<
	
	>;

	using ec_traits_t = yaecs::ec_traits<components, signatures>;
	using entity_t = yaecs::entity<ec_traits_t>;
	using ec_engine_type_t = yaecs::ec_engine<ec_traits_t>;

public:

	ec_manager() 
		: ec_engine_{ new ec_engine_type_t() }
	{
	}

	~ec_manager() 
	{
		delete ec_engine_;
	}

	inline std::uint32_t create_entity() noexcept {
		return ec_engine_->create_entity();
	}

	inline const entity_t& get_entity(std::uint32_t index) {
		return ec_engine_->get_entity(index);
	}

	inline std::uint32_t entity_count() const noexcept {
		return ec_engine_->entity_count();
	}

	template<typename T>
	inline void add_component(std::uint32_t entity_id, T c) {
		ec_engine_->add_component<T>(entity_id, std::forward<T>(c));
	}

	template<typename T>
	inline void add_component(std::uint32_t entity_id) {
		ec_engine_->add_component<T>();
	}

	template<typename T, class callable>
	inline void each(callable c) {
		ec_engine_->each<T>(std::forward<callable>(c));
	}

	template<typename... Ts, class callable>
	inline void for_matching_entities(callable c) {
		ec_engine_->for_matching_entities<Ts...>(std::forward<callable>(c));
	}


private:
	ec_engine_type_t* ec_engine_{nullptr};
};

} // namespace bravo6