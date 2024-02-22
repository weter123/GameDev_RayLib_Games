#include "raylib.h"

int main(){

    const int width = 512;
    const int height = 380;

    InitWindow(width, height, "Dapper Dasher");

    const int gravity = 1000;

    //Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    int nebVal = -200;

    //Nebula 1
    Rectangle nebRec;
    nebRec.width = nebula.width/8;
    nebRec.height = nebula.height/8;
    nebRec.x = 0;
    nebRec.y = 0;
    Vector2 nebPos;
    nebPos.x = width;
    nebPos.y = height - nebRec.height;

    
    const float nebUpdateTime = 1.0/12.0;
    float nebRunningTime = 0.0;
    int nebFrame = 0;

    //Nebula 2
    Rectangle neb2Rec;
    neb2Rec.width = nebula.width/8;
    neb2Rec.height = nebula.height/8;
    neb2Rec.x = 0;
    neb2Rec.y = 0;
    Vector2 neb2Pos;
    neb2Pos.x = width + 300;
    neb2Pos.y = height - nebRec.height;

    const float neb2UpdateTime = 1.0/16.0;
    float neb2RunningTime = 0.0;
    int neb2Frame = 0;

    // Scrafy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = width/2 - scarfyRec.width/2;
    scarfyPos.y = height - scarfyRec.height;

    int velocity = 0;
    int jump = -600;
    bool isInAir = false;

    int frame = 0;
    const float updateTime = 1.0/12.0;
    float runningTime = 0.0;

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        float dt = GetFrameTime();
        if (scarfyPos.y >= height - scarfyRec.height)
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
        scarfyPos.y += velocity * dt;
        // nebula 1 movement
        nebPos.x += nebVal * dt;
        // nebula 2 movement
        neb2Pos.x += nebVal * dt;


        // Scargy Frames update
        runningTime += dt;
        if(!isInAir){
            if (runningTime >= updateTime){
                runningTime = 0.0;
                scarfyRec.x = frame * scarfyRec.width;          
                frame++;
                if(frame > 5){
                    frame = 0;
                }
            }
        }

        //Nebula 1 Frame update
        nebRunningTime += dt;
        if (nebRunningTime >= nebUpdateTime){
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(nebFrame > 7){
                nebFrame  = 0;
            }
        }

        //Nebula 2 Frame update
        neb2RunningTime += dt;
        if (neb2RunningTime >= neb2UpdateTime){
            neb2RunningTime = 0.0;
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if(neb2Frame > 7){
                neb2Frame  = 0;
            }
        }
        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        // Draw nebula 1
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        // Draw nebula 1
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);
        
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    
}