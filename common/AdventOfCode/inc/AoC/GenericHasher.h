#include <tuple>
#include <array>
#include <utility>
#include <functional>
#include <type_traits>
#include <iostream>

#ifndef NEW_AOC_GENERICHASHER_H
#define NEW_AOC_GENERICHASHER_H
template <typename T>
inline void hash_combine(std::size_t& seed, const T& value) {
    seed ^= std::hash<T>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


struct GenericHasher {
    template <typename T>
    std::size_t operator()(const T& value) const {
        return hash_impl(value);
    }

    template <typename T>
    static auto hash_impl(const T& value) -> decltype(std::hash<T>{}(value), std::size_t{}) {
        return std::hash<T>{}(value);
    }

    template <typename T1, typename T2>
    static std::size_t hash_impl(const std::pair<T1, T2>& p) {
        std::size_t seed = 0;
        hash_combine(seed, p.first);
        hash_combine(seed, p.second);
        return seed;
    }

    template <typename... Args>
    static std::size_t hash_impl(const std::tuple<Args...>& t) {
        return hash_tuple(t, std::index_sequence_for<Args...>{});
    }

    template <typename Tuple, std::size_t... Index>
    static std::size_t hash_tuple(const Tuple& t, std::index_sequence<Index...>) {
        std::size_t seed = 0;
        (..., hash_combine(seed, std::get<Index>(t)));
        return seed;
    }

    template <typename T, std::size_t N>
    static std::size_t hash_impl(const std::array<T, N>& arr) {
        std::size_t seed = 0;
        for (const auto& elem : arr) {
            hash_combine(seed, elem);
        }
        return seed;
    }
};
#endif //NEW_AOC_GENERICHASHER_H
