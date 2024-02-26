#include "raylib.h"

struct AnimData {
    Rectangle Rec;
    Vector2 Pos;
    int frame;
    float runningTime;
    float updateTime;
};

bool isOnGround(AnimData data, int windowHeight){
    
    return data.Pos.y >= windowHeight - data.Rec.height;
   
}

AnimData updateAnimData(AnimData data, float dt ){
    data.runningTime += dt;
    if (data.runningTime >= data.updateTime){
        data.runningTime = 0.0;
        data.Rec.x = data.frame * data.Rec.width;          
        data.frame++;
        if(data.frame > 5){
            data.frame = 0;
        }
    }
    return data;

}

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

        // Check if Scarfy is on ground or in air
        if (isOnGround(scarfyData, windowDimensions[1]))
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

        // Scargfy Frames update
        if(!isInAir){
           scarfyData = updateAnimData(scarfyData,dt);
        }

        // Nebulae Frames update
        for (int i = 0; i < nebulaeSize; i++){
           nebulae[i] = updateAnimData(nebulae[i], dt);
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