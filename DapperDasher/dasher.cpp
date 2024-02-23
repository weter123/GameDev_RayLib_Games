#include "raylib.h"

struct AnimData {
    Rectangle Rec;
    Vector2 Pos;
    int frame;
    float runningTime;
    float updateTime;
};

int main(){

    const int windowDimensions[2] = {512,380};
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    const int gravity = 1000;

    //Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    int nebVal = -200;
    const int nebulaeSize = 6;

    // Nebulae variable
    AnimData nebulae[nebulaeSize] = {};

    for(int i = 0 ; i < nebulaeSize; i++){
        int xPos = i*300;
        nebulae[i].Rec.width = nebula.width/8;
        nebulae[i].Rec.height = nebula.height/8;
        nebulae[i].Rec.x = 0;
        nebulae[i].Rec.y = 0;

        nebulae[i].Pos.x = windowDimensions[0] + xPos;
        nebulae[i].Pos.y = windowDimensions[1] - nebulae[i].Rec.height;

        nebulae[i].updateTime = 1.0/12.0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].frame = 0;
    }

    // Scrafy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.Rec.width = scarfy.width/6;
    scarfyData.Rec.height = scarfy.height;
    scarfyData.Rec.x = 0;
    scarfyData.Rec.y = 0;

    scarfyData.Pos.x = windowDimensions[0]/2 - scarfyData.Rec.width/2;
    scarfyData.Pos.y = windowDimensions[1] - scarfyData.Rec.height;

    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    int velocity = 0;
    int jump = -600;
    bool isInAir = false;

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        const float dt = GetFrameTime();
        if (scarfyData.Pos.y >= windowDimensions[1] - scarfyData.Rec.height)
        {
            velocity =0;
            isInAir = false;
        }else{
            velocity += gravity * dt;
            isInAir = true;
        }
        if (IsKeyPressed(KEY_SPACE) && !isInAir){
            velocity += jump;
        }

        // Scrafy Jump
        scarfyData.Pos.y += velocity * dt;

        // Nebulae Movement
        for (int i = 0; i < nebulaeSize; i++){
            nebulae[i].Pos.x += nebVal * dt;
        }


        // Scargy Frames update
        
        if(!isInAir){
            scarfyData.runningTime += dt;
            if (scarfyData.runningTime >= scarfyData.updateTime){
                scarfyData.runningTime = 0.0;
                scarfyData.Rec.x = scarfyData.frame * scarfyData.Rec.width;          
                scarfyData.frame++;
                if(scarfyData.frame > 5){
                    scarfyData.frame = 0;
                }
            }
        }

        for (int i = 0; i < nebulaeSize; i++){
            nebulae[i].runningTime += dt;
            if (nebulae[i].runningTime >= nebulae[i].updateTime){
                nebulae[i].runningTime = 0.0;
                nebulae[i].Rec.x = nebulae[i].frame * nebulae[i].Rec.width;
                nebulae[i].frame++;
                if(nebulae[i].frame > 7){
                    nebulae[i].frame  = 0;
                }
            }
        }

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.Rec, scarfyData.Pos, WHITE);
        // Draw nebulae
        for (int i = 0; i < nebulaeSize; i++){
             DrawTextureRec(nebula, nebulae[i].Rec, nebulae[i].Pos, WHITE);
        }

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
}