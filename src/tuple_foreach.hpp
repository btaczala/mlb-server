#ifndef TUPLE_FOREACH_HPP_VLIGENHY
#define TUPLE_FOREACH_HPP_VLIGENHY

#include <cstddef>
#include <tuple>

template <typename Tuple, typename Callable, std::size_t... Indices>
void for_each_impl(Tuple &&tp, Callable &&cb, std::index_sequence<Indices...>) {
    using swallow = int[];
    (void)swallow{1, (cb(std::get<Indices>(tp)), void(), int{})...};
}

template <typename Tuple, typename Callable>
void for_each(Tuple &&t, Callable &&cb) {
    constexpr std::size_t N = std::tuple_size<std::decay_t<Tuple>>::value;

    for_each_impl(std::forward<Tuple>(t), std::forward<Callable>(cb),
                  std::make_index_sequence<N>{});
}

#endif /* end of include guard: TUPLE_FOREACH_HPP_VLIGENHY */
