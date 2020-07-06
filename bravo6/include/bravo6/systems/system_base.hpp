#pragma once

namespace bravo6 {

class ec_manager;
class context;
class constructor_helper;

class system_base {
public:

	virtual ~system_base() {};

	virtual void on_load(bravo6::ec_manager* ecm, bravo6::context* ctx, bravo6::constructor_helper* cth) = 0;

	virtual void update(float delta_time, bravo6::ec_manager* ecm)  = 0;

};

} // namespace bravo6