#include <raylib.h>
#include "game.h"
#include <iostream>

int main(){
    InitWindow(500,620, "Raylib Tetris");
    SetTargetFPS(60);
    
    Color darkGrey = {44, 44, 127, 255};
    Font fontBm = LoadFont("resources/pixantiqua.fnt");
    Game game = Game();
    while (WindowShouldClose() == false)
    {
        game.HandleInput();
        BeginDrawing();
        ClearBackground(darkGrey);
        DrawText("Score", 360, 38, 25, WHITE);
        DrawRectangleRounded({320, 75, 170, 50}, 0.3, 6, BLUE );
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(fontBm, scoreText, 38, 2);

        DrawText(scoreText, 320 +(170-textSize.x)/2 , 90, 25, WHITE);
        DrawText("Next", 367, 155, 25, WHITE);
        DrawRectangleRounded({320, 185, 170, 150}, 0.3, 6, BLUE );
        DrawText("Süre", 367, 350, 25, WHITE);
        DrawRectangleRounded({320, 390, 170, 60}, 0.3, 6, BLUE );
        game.Drug();
        game.Draw();
        char time[10];
        sprintf(time, "%d", game.counter);
        Vector2 timerSize = MeasureTextEx(fontBm, time, 38, 2);
        if(game.counter < 15){
            DrawText(time, 320+(170-timerSize.x)/2, 410, 25, WHITE);
        }
        else{
            DrawText("Süre Bitti", 340, 410, 25, WHITE);
        }

        if(game.gameOver){
            DrawText("Game Over", 340, 470, 25, WHITE);
        }
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}