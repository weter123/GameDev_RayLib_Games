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

    float finishingLine = nebulae[nebulaeSize -1].Pos.x;

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

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgx = 0;

    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgx = 0;

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgx = 0;

    bool collision = false; 

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        const float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);
        bgx-=20 * dt;
        if (bgx <= -background.width*2){
            bgx =0;
        }
        // Draw Background
        Vector2 bg1Pos = {bgx,0.0};
        DrawTextureEx(background,bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos = {bgx + midground.width*2,0.0};
        DrawTextureEx(background,bg2Pos, 0.0, 2.0, WHITE);

        mgx-=40 * dt;
        if (mgx <= -midground.width*2){
            mgx =0;
        }

        Vector2 mg1Pos = {mgx,0.0};
        DrawTextureEx(midground,mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos = {mgx + midground.width*2,0.0};
        DrawTextureEx(midground,mg2Pos, 0.0, 2.0, WHITE);

        fgx-=80 * dt;
        if (fgx <= -background.width*2){
            fgx =0;
        }

        Vector2 fg1Pos = {fgx,0.0};
        DrawTextureEx(foreground,fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos = {fgx + foreground.width*2,0.0};
        DrawTextureEx(foreground,fg2Pos, 0.0, 2.0, WHITE);

        

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
        // update finishLine position
        finishingLine += nebVal * dt;

        // Scargfy Frames update
        if(!isInAir){
           scarfyData = updateAnimData(scarfyData,dt);
        }

        // Nebulae Frames update
        for (int i = 0; i < nebulaeSize; i++){
           nebulae[i] = updateAnimData(nebulae[i], dt);
        }

        // Check for Collision between scarfy and nebulae
        for ( AnimData nebula: nebulae){
            float pad = 50;
            Rectangle nebRec{nebula.Pos.x+ pad, nebula.Pos.y + pad, nebula.Rec.width - 2* pad, nebula.Rec.height -2*pad};
            Rectangle scarfyRec{scarfyData.Pos.x, scarfyData.Pos.y, scarfyData.Rec.width, scarfyData.Rec.height};
            if(CheckCollisionRecs(nebRec,scarfyRec)){
                collision = true;
            }
        }

        if (collision){
            // Collision is True, player Loses the Game
             DrawText("Game Over!", windowDimensions[0]/4, windowDimensions[1]/2 - 48, 48, RED);
            
        } else  if (scarfyData.Pos.x >= finishingLine) {
            // if scarfy reaches the finishing line, player wins
            DrawText("You Win!", windowDimensions[0]/4, windowDimensions[1]/2 - 48, 48, GREEN);
            
        } else {
            // Draw Scarfy
            DrawTextureRec(scarfy, scarfyData.Rec, scarfyData.Pos, WHITE);

            // Draw nebulae
            for (int i = 0; i < nebulaeSize; i++){
                DrawTextureRec(nebula, nebulae[i].Rec, nebulae[i].Pos, WHITE);
            }
        }
        

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
    
}