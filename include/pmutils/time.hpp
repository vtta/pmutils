#pragma once

#include <chrono>
#include <concepts>
#include <functional>
#include <type_traits>

namespace pmutils {

template <typename Callable, typename... Args>
requires std::logical_not<
    std::is_void<std::invoke_result_t<Callable, Args...>>>::value inline std::
    tuple<std::chrono::nanoseconds, std::invoke_result_t<Callable, Args...>>
    time(Callable &&f, Args &&...args) {
    using clock = std::chrono::high_resolution_clock;
    auto begin = clock::now();
    auto ret = f(std::forward<Args>(args)...);
    auto end = clock::now();
    return {end - begin, ret};
}

template <typename Callable, typename... Args>
requires std::is_void<std::invoke_result_t<Callable, Args...>>::
    value inline std::chrono::nanoseconds
    time(Callable &&f, Args &&...args) {
    using clock = std::chrono::high_resolution_clock;
    auto begin = clock::now();
    f(std::forward<Args>(args)...);
    auto end = clock::now();
    return end - begin;
}

template <typename Callable, typename... Args>
requires std::logical_not<
    std::is_void<std::invoke_result_t<Callable, Args...>>>::value inline std::
    tuple<int64_t, std::invoke_result_t<Callable, Args...>>
    cycle(Callable &&f, Args &&...args) {
    auto begin = _rdtsc();
    auto ret = f(std::forward<Args>(args)...);
    auto end = _rdtsc();
    return {end - begin, ret};
}

template <typename Callable, typename... Args>
requires std::is_void<
    std::invoke_result_t<Callable, Args...>>::value inline int64_t
cycle(Callable &&f, Args &&...args) {
    auto begin = _rdtsc();
    f(std::forward<Args>(args)...);
    auto end = _rdtsc();
    return end - begin;
}

}  // namespace pmutils