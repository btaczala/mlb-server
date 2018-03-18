#ifndef TRAITS_HPP_KWUKITQT
#define TRAITS_HPP_KWUKITQT

#include <vector>

template <class T>
struct is_container {
    constexpr static bool value = false;
};

template <>
template <class T, class Alloc>
struct is_container<std::vector<T, Alloc>> {
    constexpr static bool value = true;
};

#endif /* end of include guard: TRAITS_HPP_KWUKITQT */
