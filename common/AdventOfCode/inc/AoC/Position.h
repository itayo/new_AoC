#include "GenericHasher.h"

#ifndef NEW_AOC_POSITION_H
#define NEW_AOC_POSITION_H
namespace AoC {
    struct Position {
        std::array<int32_t, 2> coords{};

        int32_t &operator[](std::size_t index) { return coords[index]; }

        const int32_t &operator[](std::size_t index) const { return coords[index]; }

        bool operator==(const Position &other) const {
            return coords[0] == other.coords[0] && coords[1] == other.coords[1];
        }

        bool operator!=(const Position &other) const {
            return !(*this == other);
        }

        bool operator<(const Position &other) const {
            return std::tie(coords[0], coords[1]) < std::tie(other.coords[0], other.coords[1]);
        }

        bool operator<=(const Position &other) const {
            return !(other < *this);
        }

        bool operator>(const Position &other) const {
            return other < *this;
        }

        bool operator>=(const Position &other) const {
            return !(*this < other);
        }

        size_t operator()() {
            return GenericHasher::hash_impl(coords);
        }


        Position operator+(const Position &other) const {
            return {{coords[0] + other.coords[0], coords[1] + other.coords[1]}};
        }

        Position operator-(const Position &other) const {
            return {{coords[0] - other.coords[0], coords[1] - other.coords[1]}};
        }

        Position &operator+=(const Position &other) {
            coords[0] += other.coords[0];
            coords[1] += other.coords[1];
            return *this;
        }

        Position &operator-=(const Position &other) {
            coords[0] -= other.coords[0];
            coords[1] -= other.coords[1];
            return *this;
        }

        Position operator*(int32_t scalar) const {
            return {{coords[0] * scalar, coords[1] * scalar}};
        }

        Position &operator*=(int32_t scalar) {
            coords[0] *= scalar;
            coords[1] *= scalar;
            return *this;
        }


        struct PositionHasher {
            std::size_t operator()(const Position &pos) const noexcept {
                return std::hash<int32_t>{}(pos.coords[0]) ^ (std::hash<int32_t>{}(pos.coords[1]) << 1);
            }
            static const std::size_t getHash(const Position &pos) noexcept {
                return std::hash<int32_t>{}(pos.coords[0]) ^ (std::hash<int32_t>{}(pos.coords[1]) << 1);
            }

        };
    };

    static constexpr std::array<Position, 4> PositionDirections{
            {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

}
#endif //NEW_AOC_POSITION_H
