#ifndef ADVENTOFCODE_GRID2D_H
#define ADVENTOFCODE_GRID2D_H

#include <vector>
#include <string>
#include "Vector2D.h"
#include "Assertion.h"

namespace AoC {

    template<class tType>
    class Grid2D {
    public:
        Grid2D(int p_rows, int p_cols) :
                m_rows(p_rows), m_columns(p_cols), m_cells(p_rows * p_cols) {

        };

        Grid2D(int p_rows, int p_cols, const tType &initValue) :
                m_rows(p_rows), m_columns(p_cols), m_cells(p_rows * p_cols, initValue) {

        };

        Grid2D(int p_rows, int p_cols, std::vector<tType> &data) : m_rows(p_rows), m_columns(p_cols),
                                                                   m_cells(p_rows, p_cols) {
            m_cells.clear();
            m_cells.resize(p_rows * p_cols);
            std::copy(data.begin(), data.end(), std::back_inserter(m_cells));
        }

        Grid2D() : Grid2D(0, 0) {}

        int Columns() const { return m_columns; };

        int Rows() const { return m_rows; };

        bool Exists(int p_row, int p_column) {
            return p_row >= 0 && p_column >= 0 && p_row < m_rows && p_column < m_columns;
        }

        bool Exists(Vector2D p_position) { return Exists(p_position.X(), p_position.Y()); }

        tType Get(int p_row, int p_column) {
            if (Exists(p_row, p_column)) {
                return m_cells[(m_columns * p_row) + p_column];
            }
            return tType();
        }

        bool AllExists(const std::vector<Vector2D> &Locations) {
            for (const Vector2D &location: Locations) {
                if (!Exists(location)) return false;
            }
            return true;
        }

        tType Get(Vector2D p_position) { return Get(p_position.X(), p_position.Y()); }

        tType operator[](Vector2D v) const {
            return Get(v.Y(), v.X());
        }

        tType operator[](std::pair<int, int> index) {
            return (Get(index.second, index.first));
        }

        std::string GetColumnAsString(int column) {
            std::string result = "";
            for (int i = 0; i < m_rows; ++i) {
                result += Get(i, column);
            }
            return result;
        }

        std::string GetRowAsString(int row) {
            std::string result;
            for (int i = 0; i < m_rows; ++i) {
                result += Get(row, i);
            }
            return result;

        }

        std::string GetSectorAsString(Vector2D start, Vector2D stop) {
            std::string result = "";
            for (int row = start.Y(); row <= stop.Y(); ++row) {
                for (int column = start.X(); column <= stop.X(); ++column) {
                    result += Get(row, column);
                }
            }
            return result;
        }

        void Reset(int p_row, int p_columns) {
            Reset(p_row, p_columns, tType());
        }

        void Reset(int p_row, int p_columns, tType t) {
            m_cells.clear();
            m_rows = p_row;
            m_columns = p_columns;
            m_cells.insert(m_cells.begin(), m_rows * m_columns, t);

        }

        Vector2D IndexToLocation(int index) {
            Vector2D ret{index / m_columns, index % m_columns};
            return ret;
        }

        int Vector2DToLocation(Vector2D vector) {
            return vector.Y() * m_rows + vector.X();
        }

        void Set(int p_row, int p_column, tType p_value) {
            if (Exists(p_row, p_column)) {
                m_cells[(m_columns * p_row) + p_column] = p_value;
            }
        }

        void Set(Vector2D pos, tType p_value) { Set(pos.X(), pos.Y(), p_value); }

        void SetAll(tType value) {
            for (auto &cell: m_cells) {
                cell = value;
            }
        }

        void SetRow(int p_row, tType p_value) {
            for (int column = 0; column < m_columns; ++column) {
                Set(p_row, column, p_value);
            }
        }

        void SetColumn(int p_column, tType p_value) {
            for (int row = 0; row < m_rows; ++row) {
                Set(row, p_column, p_value);
            }
        }

        int count_if(tType value) {
            return std::count_if(m_cells.begin(), m_cells.end(), [&value](tType i) { return value == i; });
        }

        void Print() {
            for (int row = 0; row < m_rows; ++row) {
                for (int cols = 0; cols < m_columns; ++cols) {
                    std::cout << Get(row, cols);
                }
                std::cout << std::endl;
            }

        }

        template<typename tPrintType>
        void Print() {
            for (int row = 0; row < m_rows; ++row) {
                for (int cols = 0; cols < m_columns; ++cols) {
                    std::cout << tPrintType(Get(row, cols));
                }
                std::cout << std::endl;
            }

        }

        void PrintWithOverlay(Vector2D overlayPos) {
            char tmp = Get(overlayPos);
            Set(overlayPos.X(), overlayPos.Y(), overlayPos.FacingSymbol());
            for (int row = 0; row < m_rows; ++row) {
                for (int cols = 0; cols < m_columns; ++cols) {
                    std::cout << Get(row, cols);
                }
                std::cout << std::endl;
            }
            Set(overlayPos.X(), overlayPos.Y(), tmp);

        }

        Vector2D FindPos(tType p_what) {
            auto it = std::find(m_cells.begin(), m_cells.end(), p_what);
            if (it == m_cells.end()) ExitIfReached();
            int index = std::distance(m_cells.begin(), it);
            ExitOnAssertFail((index < m_cells.size()));
            return (Vector2D{index % m_columns, index / m_columns});

        }

        std::vector<Vector2D> FindAllLocationsOf(tType p_what) {
            std::vector<Vector2D> locations;
            auto it = m_cells.begin();
            while ((it = std::find_if(it, m_cells.end(), [p_what](char c) { return c == p_what; })) != m_cells.end()) {
                int index = std::distance(m_cells.begin(), it);
                locations.emplace_back(IndexToLocation(index));
                it++;
            }
            return locations;
        }

        const std::vector<tType> *GetRawData() const {
            return *&m_cells;
        }

    private:
        int m_rows = 0;
        int m_columns = 0;

        std::vector<tType> m_cells;
    };
}


#endif //ADVENTOFCODE_GRID2D_H
