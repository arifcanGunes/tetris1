#pragma once
#include "grid.h"
#include "blocks.cpp"
class Game{
    public:
        Game();
        Block GetRandomBlock();
        std::vector<Block> GetAllBlocks();
        void Draw();
        void Drug();
        void HandleInput();
        Grid grid;
        bool isdrugging;
        int score;
        int counter;
        float timer;
        float interval;
        bool gameOver;
    private:
    bool isBlockOutside();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int point);
    void SecondTimer();
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};