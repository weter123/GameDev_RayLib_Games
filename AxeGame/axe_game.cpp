#include "raylib.h"
#include <stdio.h>
int main(){
    // Window Dimensions
    int width;
    int hight; 
    width = 800;
    hight = 450;
    //Circle Coordinates
    int circle_x{200};
    int circle_y{200};
    int circle_radius{25};
    // Circle Collision Variables
    int circle_l{circle_x - circle_radius};
    int circle_r{circle_x + circle_radius};
    int circle_u{circle_y - circle_radius};
    int circle_b{circle_y + circle_radius};

    //Axe Coordinates
    int axe_x{400};
    int axe_y{0};
    int direction{10};
    int axe_length{50};
    //Axe Collision Variables
    int axe_l{axe_x};
    int axe_r{axe_x + axe_length};
    int axe_u{axe_y};
    int axe_b{axe_y + axe_length};

    bool collisionWithAxe(int circle_l, int circle_r, int circle_u, int circle_b, int axe_l, int axe_r, int axe_u, int axe_b);

    InitWindow(width, hight, "Axe Game");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(GREEN);

        //Check for Circle Collission with Axe
        if(collisionWithAxe(circle_l, circle_r, circle_u, circle_b, axe_l, axe_r, axe_u, axe_b)){
            DrawText("Game Over", 300, 200, 20, RED);
        } else{
            DrawCircle(circle_x,circle_y,circle_radius,RED);
            DrawRectangle(axe_x,axe_y,axe_length,axe_length,BLUE);

            // Axe Movement
            axe_y+= direction;
            if(axe_y > hight || axe_y < 0){
                direction*=-1;
            }
            
            // Circle Movement
            if(IsKeyDown(KEY_D) && circle_x < width){
                circle_x+= 10;
            }
            if(IsKeyDown(KEY_A) && circle_x > 0){
                circle_x-= 10;
            }

            //Update Collision Variables
            circle_l=circle_x - circle_radius;
            circle_r=circle_x + circle_radius;
            circle_u=circle_y - circle_radius;
            circle_b=circle_y + circle_radius;

            axe_l=axe_x;
            axe_r=axe_x + axe_length;
            axe_u=axe_y;
            axe_b=axe_y + axe_length;
        }
        EndDrawing();
        
    }
}

bool collisionWithAxe(int circle_l, int circle_r, int circle_u, int circle_b, int axe_l, int axe_r, int axe_u, int axe_b){

    if(circle_l <= axe_r && circle_r >= axe_l && circle_b >= axe_u && circle_u <= axe_b){
        return true;
    }else{
        return false;
    }
        

}