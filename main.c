#include "include/raylib.h"
#include <stdlib.h>
#include <time.h>

#define BG_COLOR BLACK
#define FG_COLOR WHITE

int main() {
    
    const float WIDTH = 1024.0f;
    const float HEIGHT = 768.0f;
    const int WIN_LIMIT = 10;

    int paddle_A_points = 0;
    int paddle_B_points = 0;
    const float PADDLE_WIDTH = 0.02 * HEIGHT;
    const float PADDLE_HEIGHT = 0.1 * HEIGHT;
    const int BALL_VELOCITY_INCREASE_MAX = 0.5 * HEIGHT;
    const float PADDLE_MOVEMENT = 0.6 * WIDTH;
    float paddle_bounce = 0.2 * WIDTH;
    float paddle_A_y = (HEIGHT - PADDLE_HEIGHT) / 2;
    float paddle_A_velocity = 0.0f;
    float paddle_B_y = (HEIGHT - PADDLE_HEIGHT) / 2;
    float paddle_B_velocity = 0.0f;
    const float PADDLE_PADDING = 0.005 * WIDTH;
    const float HALFLINE_WIDTH = 0.005 * WIDTH;
    const float BALL_SIZE = 0.02 * WIDTH;
    float ball_x = (WIDTH - BALL_SIZE) / 2.0f;
    float ball_y = (HEIGHT - BALL_SIZE) / 2.0f;
    float ball_velocity_x = 0.6 * WIDTH;
    float ball_velocity_y = 0.0f;
    const float BALL_VELOCITY_Y_LIMIT = 1.04 * HEIGHT;
    const float FONT_SIZE = 0.1 * WIDTH;


    srand(time(NULL));

    InitWindow(WIDTH, HEIGHT, "PONG");
    while(!WindowShouldClose()){
        float dt = GetFrameTime();

        if(IsKeyDown(KEY_W)){
            paddle_A_velocity = -PADDLE_MOVEMENT;
        } else if(IsKeyDown(KEY_S)){
            paddle_A_velocity = PADDLE_MOVEMENT;
        } else{
            paddle_A_velocity = 0;
        }

        if(IsKeyDown(KEY_UP)){
            paddle_B_velocity = -PADDLE_MOVEMENT;
        } else if(IsKeyDown(KEY_DOWN)){
            paddle_B_velocity = PADDLE_MOVEMENT;
        } else{
            paddle_B_velocity = 0;
        }

        if(IsKeyPressed(KEY_BACKSPACE)){
            paddle_A_points = 0;
            paddle_B_points = 0;
            paddle_A_velocity = 0;
            paddle_A_y = (HEIGHT - PADDLE_HEIGHT) / 2;
            paddle_B_velocity = 0;
            paddle_B_y = (HEIGHT - PADDLE_HEIGHT) / 2;
            ball_velocity_x = 0.59 * WIDTH;
            ball_velocity_y = 0;
            ball_x = (WIDTH - BALL_SIZE) / 2;
            ball_y = (HEIGHT - BALL_SIZE) / 2;
        }

        if(paddle_A_y < 0){
            paddle_A_y = 0;
            paddle_A_velocity = 0;
        }

        if(paddle_B_y < 0){
            paddle_B_y = 0;
            paddle_B_velocity = 0;
        }

        if(paddle_A_y > HEIGHT - PADDLE_HEIGHT){
            paddle_A_y = HEIGHT - PADDLE_HEIGHT;
            paddle_A_velocity = 0;
        }

        if(paddle_B_y > HEIGHT - PADDLE_HEIGHT){
            paddle_B_y = HEIGHT - PADDLE_HEIGHT;
            paddle_B_velocity = 0;
        }

        if(ball_y < 0){
            ball_y = 0;
            ball_velocity_y *= -1;
        }

        if(ball_y > HEIGHT - BALL_SIZE){
            ball_y = HEIGHT - BALL_SIZE;
            ball_velocity_y *= -1;
        }

        if(ball_x < 0){
            ball_x = WIDTH / 2.0f;
            ball_y = HEIGHT / 2.0f;
            ball_velocity_x = 0.59 * WIDTH;
            ball_velocity_y = 0.0f;
            paddle_B_points += 1;
        }

        if(ball_x > WIDTH - BALL_SIZE - 5){
            ball_x = WIDTH / 2.0f;
            ball_y = HEIGHT / 2.0f;
            ball_velocity_x = -0.59 * WIDTH;
            ball_velocity_y = 0.0f;
            paddle_A_points += 1;
        }

        ball_x += ball_velocity_x * dt;
        ball_y += ball_velocity_y * dt;
        paddle_A_y += paddle_A_velocity * dt;
        paddle_B_y += paddle_B_velocity * dt;

        BeginDrawing();
        ClearBackground(BG_COLOR);

        Rectangle paddle_A = {PADDLE_PADDING, paddle_A_y, PADDLE_WIDTH, PADDLE_HEIGHT};
        Rectangle paddle_B = {WIDTH - PADDLE_PADDING - PADDLE_WIDTH, paddle_B_y, PADDLE_WIDTH, PADDLE_HEIGHT};
        Rectangle ball = {ball_x, ball_y, BALL_SIZE, BALL_SIZE};

        if(CheckCollisionRecs(ball, paddle_A) && ball_velocity_x < 0){
            ball_velocity_x *= -1;
            paddle_bounce = (rand() % BALL_VELOCITY_INCREASE_MAX + 1);
            if(paddle_A_velocity < 0){
                ball_velocity_y -= paddle_bounce;
            } 
            else if(paddle_A_velocity > 0){
                ball_velocity_y += paddle_bounce;
            }
            ball_x = 5 + PADDLE_WIDTH;
        }  

        if(CheckCollisionRecs(ball, paddle_B) && ball_velocity_x > 0){
            ball_velocity_x *= -1;
            paddle_bounce = (rand() % BALL_VELOCITY_INCREASE_MAX + 1);
            if(paddle_B_velocity < 0){
                ball_velocity_y -= paddle_bounce;
            } 
            else if(paddle_B_velocity > 0){
                ball_velocity_y += paddle_bounce;
            }
            ball_x = WIDTH - 5 - PADDLE_WIDTH - BALL_SIZE;
        }

        if(ball_velocity_y > BALL_VELOCITY_Y_LIMIT){
            ball_velocity_y = BALL_VELOCITY_Y_LIMIT;
        }
        if(ball_velocity_y < -BALL_VELOCITY_Y_LIMIT){
            ball_velocity_y = -BALL_VELOCITY_Y_LIMIT;
        }

        DrawRectangleRec(paddle_A, FG_COLOR);
        DrawRectangleRec(paddle_B, FG_COLOR);
        DrawRectangleRec(ball, FG_COLOR);
        DrawRectangle((WIDTH / 2) - (HALFLINE_WIDTH / 2), 0, HALFLINE_WIDTH, HEIGHT, FG_COLOR);
        DrawText(TextFormat("%d", paddle_A_points), 0.29 * WIDTH, 0.02 * HEIGHT, FONT_SIZE, FG_COLOR);
        DrawText(TextFormat("%d", paddle_B_points), 0.67 * WIDTH, 0.02 * HEIGHT, FONT_SIZE, FG_COLOR);

        if(paddle_A_points == WIN_LIMIT || paddle_B_points == WIN_LIMIT){
            ball_velocity_x = 0;
            ball_velocity_y = 0;
            ball_x = (WIDTH - BALL_SIZE) / 2;
            ball_y = (HEIGHT - BALL_SIZE) / 2;
            paddle_A_y = ((HEIGHT - PADDLE_HEIGHT) / 2);
            paddle_B_y = ((HEIGHT - PADDLE_HEIGHT) / 2);
            DrawRectangle(0, 0, WIDTH, HEIGHT, BG_COLOR);
            if(paddle_A_points > paddle_B_points){
                DrawText(TextFormat("Player A Won!"), 0.15 * WIDTH, 0.434 * HEIGHT, FONT_SIZE, FG_COLOR);
            }
            if(paddle_B_points > paddle_A_points){
                DrawText(TextFormat("Player B Won!"), 0.15 * WIDTH, 0.434 * HEIGHT, FONT_SIZE, FG_COLOR);
            }
        }
        
        EndDrawing();
    };
    CloseWindow();

    return 0;
}
