#include "raylib.h"

struct AnimData {
    Rectangle Rec;
    Vector2 Pos;
    int frame;
    float runningTime;
    float updateTime;
};

int main(){

    const int width = 512;
    const int height = 380;

    InitWindow(width, height, "Dapper Dasher");

    const int gravity = 1000;

    //Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    int nebVal = -200;

    //Nebula 1

    AnimData neb1;
    neb1.Rec.width = nebula.width/8;
    neb1.Rec.height = nebula.height/8;
    neb1.Rec.x = 0;
    neb1.Rec.y = 0;

    neb1.Pos.x = width;
    neb1.Pos.y = height - neb1.Rec.height;

    neb1.updateTime = 1.0/12.0;
    neb1.runningTime = 0.0;
    neb1.frame = 0;

    //Nebula 2
    AnimData neb2;
    neb2.Rec.width = nebula.width/8;
    neb2.Rec.height = nebula.height/8;
    neb2.Rec.x = 0;
    neb2.Rec.y = 0;

    neb2.Pos.x = width + 300;
    neb2.Pos.y = height - neb2.Rec.height;

    neb2.updateTime = 1.0/16.0;
    neb2.runningTime = 0.0;
    neb2.frame = 0;

    // Scrafy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.Rec.width = scarfy.width/6;
    scarfyData.Rec.height = scarfy.height;
    scarfyData.Rec.x = 0;
    scarfyData.Rec.y = 0;

    scarfyData.Pos.x = width/2 - scarfyData.Rec.width/2;
    scarfyData.Pos.y = height - scarfyData.Rec.height;

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
        if (scarfyData.Pos.y >= height - scarfyData.Rec.height)
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
        // nebula 1 movement
        neb1.Pos.x += nebVal * dt;
        // nebula 2 movement
        neb2.Pos.x += nebVal * dt;


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

        //Nebula 1 Frame update
        neb1.runningTime += dt;
        if (neb1.runningTime >= neb1.updateTime){
            neb1.runningTime = 0.0;
            neb1.Rec.x = neb1.frame * neb1.Rec.width;
            neb1.frame++;
            if(neb1.frame > 7){
                neb1.frame  = 0;
            }
        }

        //Nebula 2 Frame update
        neb2.runningTime += dt;
        if (neb2.runningTime >= neb2.updateTime){
            neb2.runningTime = 0.0;
            neb2.Rec.x = neb2.frame * neb2.Rec.width;
            neb2.frame++;
            if(neb2.frame > 7){
                neb2.frame  = 0;
            }
        }
        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.Rec, scarfyData.Pos, WHITE);
        // Draw nebula 1
        DrawTextureRec(nebula, neb1.Rec, neb1.Pos, WHITE);
        // Draw nebula 1
        DrawTextureRec(nebula, neb2.Rec, neb2.Pos, RED);
        
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
}