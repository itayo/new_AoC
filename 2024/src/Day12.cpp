#include "Day12.h"
#include <queue>
#include <set>

void Day12::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.rows = raw.size();
    formatted.cols = raw[0].size();
    std::copy(raw.begin(), raw.end(), std::back_inserter(formatted.raw));

}

uint64_t Day12::Execute1(Data data) {
    uint64_t result = 0;
    std::vector<std::vector<bool>> visited(data.rows, std::vector<bool>(data.cols, false));
    static const std::vector<std::pair<uint64_t, uint64_t>> directions = {{-1, 0},
                                                                          {1,  0},
                                                                          {0,  -1},
                                                                          {0,  1}};

    for (size_t row = 0; row < data.rows; ++row) {
        for (size_t col = 0; col < data.cols; ++col) {
            uint64_t area = 0, perimeter = 0;
            if (!visited[row][col]) {
                std::queue<std::pair<uint64_t, uint64_t>> Q;
                const char plantType = data.raw[row][col];

                Q.emplace(row, col);
                visited[row][col] = true;

                while (!Q.empty()) {
                    auto [cRow, cCol] = Q.front();
                    Q.pop();

                    ++area;
                    for (const auto &[dRow, dCol]: directions) {
                        uint64_t nRow = cRow + dRow;
                        uint64_t nCol = cCol + dCol;

                        if (nRow < 0 || nCol < 0 || nRow >= data.rows || nCol >= data.cols ||
                            data.raw[nRow][nCol] != plantType) {
                            perimeter++;
                        } else if (!visited[nRow][nCol]) {
                            visited[nRow][nCol] = true;
                            Q.push({nRow, nCol});
                        }
                    }


                }

            }
            result += area * perimeter;
        }
    }

    return result;

}
int Day12::sides(const std::vector<std::vector<char>>& grid, const std::vector<std::vector<char>>& gridCopy, int row, int col) {
    auto inBounds = [](int row, int col, int rows, int cols) {
        return 0 <= row && row < rows && 0 <= col && col < cols;
    };
    int sideCount = 0;
    char plant = grid[row][col];

    for (int i = 0; i < 4; ++i) {
        int newR = row + dR[i];
        int newC = col + dC[i];

        if (!inBounds(newR, newC, grid.size(), grid[0].size()) || gridCopy[newR][newC] != plant) {
            int newR_90CC = row + dR[(i - 1 + 4) % 4];
            int newC_90CC = col + dC[(i - 1 + 4) % 4];
            bool isBeginEdge = !inBounds(newR_90CC, newC_90CC, grid.size(), grid[0].size()) || gridCopy[newR_90CC][newC_90CC] != plant;

            int newR_Corner = newR + dR[(i - 1 + 4) % 4];
            int newC_Corner = newC + dC[(i - 1 + 4) % 4];
            bool isConcaveBeginEdge = inBounds(newR_Corner, newC_Corner, grid.size(), grid[0].size()) && gridCopy[newR_Corner][newC_Corner] == plant;

            if (isBeginEdge || isConcaveBeginEdge) {
                ++sideCount;
            }
        }
    }
    return sideCount;
}


int Day12::priceRegionSides(std::vector<std::vector<char>> &grid, const std::vector<std::vector<char>> &gridCopy,
                            int startRow, int startCol) {
    auto inBounds = [](int row, int col, int rows, int cols) {
        return 0 <= row && row < rows && 0 <= col && col < cols;
    };
    int area = 1;
    int regionSides = sides(grid, gridCopy, startRow, startCol);

    char plant = grid[startRow][startCol];
    std::queue<std::pair<int, int>> q;
    q.push({startRow, startCol});
    grid[startRow][startCol] = '#'; // Mark visited

    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int newR = row + dR[i];
            int newC = col + dC[i];

            if (inBounds(newR, newC, grid.size(), grid[0].size()) && grid[newR][newC] == plant) {
                area++;
                regionSides += sides(grid, gridCopy, newR, newC);
                grid[newR][newC] = '#';
                q.push({newR, newC});
            }
        }
    }
    return area * regionSides;
}


uint64_t Day12::Execute2(Data data) {
    uint64_t result = 0;
    std::vector<std::vector<char>> grid, gridCopy;
    for(auto g: data.raw) grid.push_back(std::vector<char>(g.begin(),g.end()));
    gridCopy=grid;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid[0].size(); ++y) {
            if (grid[x][y] != '#') {
                result += priceRegionSides(grid, gridCopy, x, y);
            }
        }
    }
    return result;

}


bool Day12::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day12::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day12::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day12::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
