#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block{
    public:
        Block();
        void Draw(int offsetX, int offsetY);
        void Move(int rows, int columns);
        std::vector<Position> GetCellPositions();
        int id;
        int xCoordidante;
        int yCoordinate;
        bool isDrugging;
        std::map<int, std::vector<Position>> cells;
    private:
        int rowOffset;
        int columnOffset;
        int cellSize;
        int rotationState;
        std::vector<Color> colors;
};