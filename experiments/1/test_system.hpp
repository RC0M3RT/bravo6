#pragma once

#include <bravo6/systems/system_base.hpp>
#include <cstdint>
#include <bravo6/core/shader_helper.hpp>
#include <bravo6/core/components/c_model_view_projection.hpp>

namespace test {

class test_system_1 : public bravo6::system_base {
public:

	test_system_1();
	~test_system_1() override;

	void on_load(bravo6::ec_manager* ecm, bravo6::context* ctx, bravo6::constructor_helper* cth) override;

	void update(float delta_time, bravo6::ec_manager* ecm) override;

private:
};

}