#ifndef ADVENTOFCODE_VECTOR2D_H
#define ADVENTOFCODE_VECTOR2D_H

#include <vector>
#include <string>

namespace AoC {
    class Vector2D {
    public:
        enum tFacing {
            NORTH = 0,
            EAST = 1,
            SOUTH = 2,
            WEST = 3
        };

        Vector2D() : m_x(0), m_y(0) {}

        explicit Vector2D(int64_t p_x, int64_t p_y) : m_x(p_x), m_y(p_y) {
        }

        Vector2D(int64_t p_x, int64_t p_y, tFacing p_facing) : m_x(p_x), m_y(p_y), m_facing(p_facing) {
        }

        bool operator==(const Vector2D &lhs) const {
            return m_x == lhs.m_x && m_y == lhs.m_y && m_facing == lhs.m_facing;
        }

        bool operator!=(const Vector2D &lhs) const {
            return m_x != lhs.m_x || m_y != lhs.m_y || m_facing != lhs.m_facing;
        }

        Vector2D operator%(const Vector2D &b) {
            int64_t x = (m_x % b.m_x + b.m_x) % b.m_x;
            int64_t y = (m_y % b.m_y + b.m_y) % b.m_y;
            return Vector2D(x, y);
        }
        bool operator<(const Vector2D& b) const
        {
            if(m_x < b.m_x) return true;
            if(m_x == b.m_x && m_y < b.m_y) return true;
            return false;
        }


        Vector2D operator+(const Vector2D &v) const {
            return Vector2D(m_x + v.m_x, m_y + v.m_y);
        }

        Vector2D &operator+=(const Vector2D &rhs) {
            this->m_x += rhs.m_x;
            this->m_y += rhs.m_y;
            return *this;
        }


        Vector2D &operator-=(const Vector2D &rhs) {
            this->m_x -= rhs.m_x;
            this->m_y -= rhs.m_y;
            return *this;
        }

        Vector2D operator-(const Vector2D &v) const {
            return Vector2D(m_x - v.m_x, m_y - v.m_y);
        }

        Vector2D operator*(uint64_t v) const {
            return Vector2D(this->m_x * v, this->m_y * v);
        }

        Vector2D operator*=(uint64_t v) const {
            this->m_x * v;
            this->m_y * v;
            return *this;
        }

        void Override(int64_t x, int64_t y) {
            m_x = x;
            m_y = y;
        }

        void Override(int64_t x, int64_t y, tFacing facing) {
            m_x = x;
            m_y = y;
            m_facing = facing;
        }

        void Override(Vector2D o) {
            m_x = o.X();
            m_y = o.Y();
            m_facing = o.IsFacing();
        }

        void Override(tFacing facing) {
            m_facing = facing;
        }

        void X(int64_t p_x) { m_x = p_x; }

        int64_t X() const { return m_x; }

        void Y(int64_t p_y) { m_y = p_y; }

        int64_t Y() const { return m_y; }

        void SetFacing(tFacing facing) { m_facing=facing; }

        void TurnLeft() { m_facing = static_cast<tFacing>((m_facing + 3) % (WEST + 1)); }

        void TurnRight() { m_facing = static_cast<tFacing>((m_facing + 1) % (WEST + 1)); }

        void GoForward() {
            switch (m_facing) {
                case NORTH:
                    return GoNorth();
                case EAST:
                    return GoEast();
                case SOUTH:
                    return GoSouth();
                case WEST:
                    return GoWest();
            }
        }

        char FacingSymbol() {
            switch (m_facing) {
                case NORTH:
                    return '^';
                case EAST:
                    return '>';
                case SOUTH:
                    return 'v';
                case WEST:
                    return '<';
            }
            return NORTH;
        }

        void GoNorth() { m_x--; }

        void GoEast() { m_y++; }

        void GoSouth() { m_x++; }

        void GoWest() { m_y--; }


        const Vector2D LookAhead() {
            Vector2D inFront(m_x, m_y, m_facing);
            inFront.GoForward();
            return std::move(inFront);


        }

        tFacing IsFacing() { return m_facing; }

        void Print() {
            std::cout << "X=" << m_x << " Y=" << m_y << " Facing=" << m_facing << std::endl;
        }

        std::string Cord(bool facing = false) const {
            std::string ret = "(";
            ret += std::to_string(m_x);
            ret += ",";
            ret += std::to_string(m_y);
            if (facing) {
                ret += ",";
                ret += std::to_string(m_facing);
            }
            ret += ")";
            return ret;
        }

    private:
        tFacing m_facing = tFacing::NORTH;
        int64_t m_y = 0;

    protected:
        int64_t m_x = 0;
    };

        struct Vector2DHash {
            std::size_t operator()(const Vector2D &v) const noexcept {
                std::size_t h1 = std::hash<int64_t>{}(v.X());
                std::size_t h2 = std::hash<int64_t>{}(v.Y());
                return h1 ^ (h2 << 1); //
            }
        };
}



#endif //ADVENTOFCODE_GRID2D_H
