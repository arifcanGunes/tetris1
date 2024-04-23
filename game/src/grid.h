#pragma once
#include <vector>
#include <raylib.h>

class Grid{
    public:
        Grid();
        void Initialize();
        void Draw();
        bool isCellOutside(int row, int column);
        bool isCellEmpty(int row, int column);
        int ClearFullRow();
        int grid[20][10];
    private:
        bool isRowFull(int row);
        void ClearRow(int row);
        int numRows;
        int numCols;
        int cellSize;
        std::vector<Color> colors;
};