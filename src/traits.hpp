#ifndef TRAITS_HPP_KWUKITQT
#define TRAITS_HPP_KWUKITQT

#include <map>
#include <vector>

template <class T>
struct is_vector {
    constexpr static bool value = false;
};

template <class T, class Alloc>
struct is_vector<std::vector<T, Alloc>> {
    constexpr static bool value = true;
};

template <typename T>
struct is_map {
    constexpr static bool value = false;
};

template <typename Key, typename Value, typename Compare, typename Alloc>
struct is_map<std::map<Key, Value, Compare, Alloc>> {
    constexpr static bool value = true;
};

#endif /* end of include guard: TRAITS_HPP_KWUKITQT */
