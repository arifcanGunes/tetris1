#include "game.h"
#include <random>
#include <iostream>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = currentBlock;
    isdrugging = false;
    score = 0;
    counter = 0;
    timer = 0.0f;
    interval = 1.0f;
    gameOver = false;
}

Block Game::GetRandomBlock(){
    if(blocks.empty()){
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), OBlock(), JBlock(), LBlock(), SBlock(), OBlock(), ZBlock()};
}   

void Game::Draw(){
    grid.Draw();
    SecondTimer();
    if(counter >= 15){
        counter = 15;
        gameOver = true;
    }
    if(nextBlock.id == 3){
        nextBlock.xCoordidante = 345;
        nextBlock.yCoordinate = 245;
        nextBlock.Draw(nextBlock.xCoordidante, nextBlock.yCoordinate);
    }
    else if(nextBlock.id == 4){
        nextBlock.xCoordidante = 375;
        nextBlock.yCoordinate = 230;
        nextBlock.Draw(nextBlock.xCoordidante,nextBlock.yCoordinate);
    }
    else{
        nextBlock.xCoordidante = 360;
        nextBlock.yCoordinate = 230;
        nextBlock.Draw(nextBlock.xCoordidante,nextBlock.yCoordinate);
    }
    if(isdrugging){
        currentBlock.Draw(11,11);
    }
}

void Game::Drug(){
    int myx = GetMouseX();
    int myy = GetMouseY();

    if(myx>=360 && myx<=470){
        if(myy>= 200 && myy<= 300){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                isdrugging = true;
            }      
        }
    }
}

void Game::HandleInput(){
    int keyPressed = GetKeyPressed();
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveLeft();
        break;
    case KEY_RIGHT:
        MoveRight();
        break;
    case KEY_DOWN:
        MoveDown();
        break;
    case KEY_UP:
        MoveUp();
        break;
    case KEY_ENTER:
        LockBlock();
        break;
    case KEY_R:
        Reset();
    default:
        break;
    }
}

bool Game::isBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles){
        if(grid.isCellOutside(item.row, item.column)){
            return true;
        }
    }
    return false;
    
}

void Game::MoveLeft()
{
    if(!gameOver){
        currentBlock.Move(0,-1);
        if(isBlockOutside() || BlockFits() == false){
            currentBlock.Move(0,1);
        }
    }
    
}

void Game::MoveRight(){
    if(!gameOver){
        currentBlock.Move(0,1);
        if(isBlockOutside() || BlockFits() == false){
            currentBlock.Move(0,-1);
        }
    }
    
}

void Game::MoveUp(){
    if(!gameOver){
        currentBlock.Move(-1,0);
        if(isBlockOutside() || BlockFits() == false){
            currentBlock.Move(1,0);
        }
    }
}

void Game::MoveDown(){
    if(!gameOver){
        currentBlock.Move(1,0);
        if(isBlockOutside() || BlockFits() == false){
            currentBlock.Move(-1,0);
        }
    }
}

void Game::LockBlock()
{
    
    if(BlockFits()){
        std::vector<Position> tiles = currentBlock.GetCellPositions();
        for(Position item: tiles){
            grid.grid[item.row][item.column] = currentBlock.id;
        }
        currentBlock = nextBlock;
        nextBlock = GetRandomBlock();
        int clearedRows = grid.ClearFullRow();
        std::cout<<clearedRows<<std::endl;
        UpdateScore(clearedRows, 0);
        UpdateScore(0, 5);
        counter = 0;
        SecondTimer();
    }   
    else{
        DrawText("Blok Dolu", 350, 480, 25, WHITE);
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item : tiles){
        if(grid.isCellEmpty(item.row, item.column) == false){
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = currentBlock;
    score = 0;
    gameOver = false;
}

void Game::UpdateScore(int linesCleared, int point)
{
    switch (linesCleared)
    {
    case 1:
        score+= 100;
        break;
    case 2:
        score+= 300;
        break;
    case 3:
        score+= 500;
        break;
    
    default:
        break;
    }
    score+= point;
}

void Game::SecondTimer(){
    float deltaTime = GetFrameTime();
    timer += deltaTime;
    if (timer >= interval) {
        counter++;
        timer = 0.0f; // Timer'ı sıfırla
    }
}


