#pragma once

#include <type_traits>

namespace bravo6 {

template<typename T>
class observer_ptr {
public:

	constexpr observer_ptr() noexcept = default;
	constexpr observer_ptr(T* ptr) noexcept : ptr_{ ptr } { }

	T& operator*() const noexcept = delete;

	operator bool() const noexcept { return (ptr_ != nullptr); }

	T* operator->() const noexcept { return ptr_; }

private:
	T* ptr_{nullptr};
};

} // namespace bravo6