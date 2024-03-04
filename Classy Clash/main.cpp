#include "raylib.h"
#include "raymath.h"

int main(){
    const int windowDimensions[2] = {384,384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");

    Texture2D map = LoadTexture("OpenWorldMap24x24.png");
    Vector2 mapPos= {0,0};

    Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");

    Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");

    Texture2D knghtActive;

    Vector2 knightPos = {
        (float)windowDimensions[0]/2.0f - (0.5f * (float)knightIdle.width/6.0f),
        (float)windowDimensions[1]/2.0f - (0.5f * (float)knightIdle.height)                        
    };

    
    float speed= 4.0;
    float rightLeft = 1.f;

    float runningTime = 0.0;
    int frame =0;
    const int maxFrame = 6;
    const float updateTime = 1.f/12.f;

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction = {0.0,0.0};
        if(IsKeyDown(KEY_A)){
            direction.x -= 1.0;
        }

        if(IsKeyDown(KEY_D)){
            direction.x += 1.0;
        }

        if(IsKeyDown(KEY_W)){
            direction.y -= 1.0;
        }

        if(IsKeyDown(KEY_S)){
            direction.y += 1.0;
        }

        if( Vector2Length(direction) != 0.0){

            Vector2Normalize(direction);
            mapPos = Vector2Subtract(mapPos,Vector2Scale(direction, speed));
            direction.x < 0.f ?  rightLeft =-1.f: rightLeft = 1.f;
            knghtActive = knightRun;
            
        } else {
            knghtActive = knightIdle;
        }


        DrawTextureEx(map,mapPos, 0.0,4.0, WHITE);

        runningTime += GetFrameTime();

        if(runningTime >= updateTime){
            frame++;
            runningTime =0.f;
            if (frame > maxFrame){
                frame = 0;
            }
        }

        Rectangle knightSource;
        knightSource.width = rightLeft * (float)knightIdle.width/6.0f;
        knightSource.height= (float)knightIdle.height;
        knightSource.x = frame * (float)knightIdle.width/6.0f;
        knightSource.y = 0.f;
    
        Rectangle knightDest;
        knightDest.width = 4.0f * (float)knightIdle.width/6.0f;
        knightDest.height= 4.0f * (float)knightIdle.height;
        knightDest.x = knightPos.x;
        knightDest.y = knightPos.y;


        DrawTexturePro(knghtActive,knightSource,knightDest,Vector2{}, 0.f, WHITE);
        
        EndDrawing();
    }
}