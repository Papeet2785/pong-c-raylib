#include "include/raylib.h"
#include <stdlib.h>
#include <time.h>

#define BG_COLOR BLACK
#define FG_COLOR WHITE
#define FAIL_COLOR RED

int main() {
    
    const float WIDTH = 1024.0f;
    const float HEIGHT = 768.0f;
    const int FAIL_LIMIT = 3;

    int fail = 0;
    const float PADDLE_WIDTH = 0.02f * HEIGHT;
    const float PADDLE_HEIGHT = 0.1f * HEIGHT;
    const int BOUNCE_MIN = 0.2f * HEIGHT;
    const int BOUNCE_MAX = 0.5f * HEIGHT;
    const float PADDLE_MOVEMENT = 0.6f * WIDTH;
    float bounce = 0.2f * WIDTH;
    float paddle_A_y = (HEIGHT - PADDLE_HEIGHT) / 2.0f;
    float paddle_A_velocity = 0.0f;
    const float PADDLE_PADDING = 0.005f * WIDTH;
    const float BALL_SIZE = 0.02f * WIDTH;
    float ball_x = (WIDTH - BALL_SIZE) / 2.0f;
    float ball_y = (HEIGHT - BALL_SIZE) / 2.0f;
    float ball_velocity_x = 0.6f * WIDTH;
    float ball_velocity_y = 0.0f;
    const float BALL_VELOCITY_Y_LIMIT = 1.04f * HEIGHT;
    const float FONT_SIZE = 0.1f * WIDTH;


    srand(time(NULL));

    InitWindow(WIDTH, HEIGHT, "PONG");
    while(!WindowShouldClose()){
        float dt = GetFrameTime();

        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
            paddle_A_velocity = -PADDLE_MOVEMENT;
        } else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
            paddle_A_velocity = PADDLE_MOVEMENT;
        } else{
            paddle_A_velocity = 0.0f;
        }

        if(IsKeyPressed(KEY_BACKSPACE)){
            fail = 0;
            paddle_A_velocity = 0.0f;
            paddle_A_y = (HEIGHT - PADDLE_HEIGHT) / 2.0f;
            ball_velocity_x = 0.59f * WIDTH;
            ball_velocity_y = 0.0f;
            ball_x = (WIDTH - BALL_SIZE) / 2.0f;
            ball_y = (HEIGHT - BALL_SIZE) / 2.0f;
        }

        if(paddle_A_y < 0.0f){
            paddle_A_y = 0.0f;
            paddle_A_velocity = 0.0f;
        }

        if(paddle_A_y > HEIGHT - PADDLE_HEIGHT){
            paddle_A_y = HEIGHT - PADDLE_HEIGHT;
            paddle_A_velocity = 0.0f;
        }

        if(ball_y < 0){
            ball_y = 0.0f;
            ball_velocity_y *= -1.0f;
        }

        if(ball_y > HEIGHT - BALL_SIZE){
            ball_y = HEIGHT - BALL_SIZE;
            ball_velocity_y *= -1.0f;
        }

        if(ball_x < 0){
            ball_x = WIDTH / 2.0f;
            ball_y = HEIGHT / 2.0f;
            ball_velocity_x = 0.59f * WIDTH;
            ball_velocity_y = 0.0f;
            fail++;
        }

        if(ball_x > WIDTH - BALL_SIZE){
            ball_velocity_x *= -1;
            ball_x = WIDTH - BALL_SIZE;
        }

        ball_x += ball_velocity_x * dt;
        ball_y += ball_velocity_y * dt;
        paddle_A_y += paddle_A_velocity * dt;

        BeginDrawing();
        ClearBackground(BG_COLOR);

        Rectangle paddle_A = {PADDLE_PADDING, paddle_A_y, PADDLE_WIDTH, PADDLE_HEIGHT};
        Rectangle ball = {ball_x, ball_y, BALL_SIZE, BALL_SIZE};

        if(CheckCollisionRecs(ball, paddle_A) && ball_velocity_x < 0){
            ball_velocity_x *= -1.0f;
            bounce = (rand() % (BOUNCE_MAX - BOUNCE_MIN + 1) + BOUNCE_MIN);
            if(paddle_A_velocity < 0){
                ball_velocity_y -= bounce;
            } 
            else if(paddle_A_velocity > 0){
                ball_velocity_y += bounce;
            }
            ball_x = PADDLE_PADDING + PADDLE_WIDTH;
        }

        if(ball_velocity_y > BALL_VELOCITY_Y_LIMIT){
            ball_velocity_y = BALL_VELOCITY_Y_LIMIT;
        }
        if(ball_velocity_y < -BALL_VELOCITY_Y_LIMIT){
            ball_velocity_y = -BALL_VELOCITY_Y_LIMIT;
        }

        DrawRectangleRec(paddle_A, FG_COLOR);
        DrawRectangleRec(ball, FG_COLOR);
        DrawText(TextFormat("%d", fail), 0.49f * WIDTH, 0.1f * HEIGHT, FONT_SIZE, FAIL_COLOR);

        if(fail >= FAIL_LIMIT){
            ball_velocity_x = 0.0f;
            ball_velocity_y = 0.0f;
            ball_x = (WIDTH - BALL_SIZE) / 2.0f;
            ball_y = (HEIGHT - BALL_SIZE) / 2.0f;
            paddle_A_y = (HEIGHT - PADDLE_HEIGHT) / 2.0f;
            paddle_A_velocity = 0.0f;
            DrawRectangle(0.0f, 0.0f, WIDTH, HEIGHT, BG_COLOR);
            DrawText("GAME OVER!", 0.2f * WIDTH, 0.45f * HEIGHT, FONT_SIZE, FAIL_COLOR);
        }

        EndDrawing();
    };
    CloseWindow();

    return 0;
}
