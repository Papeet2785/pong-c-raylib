#include "include/raylib.h"

#define BG_COLOR BLACK
#define FG_COLOR WHITE

int main() {
    
    const float WIDTH = 1024.0f;
    const float HEIGHT = 768.0f;
    const int PADDLE_WIDTH = 14;
    const float PADDLE_HEIGHT = 80.0f;
    const float PADDLE_MOVEMENT = 500.0f;
    const int PADDLE_BOUNCE = 400;
    float paddle_A_y = HEIGHT / 2 - PADDLE_HEIGHT / 2;
    float paddle_B_y = HEIGHT / 2 - PADDLE_HEIGHT / 2;
    const float HALFLINE_WIDTH = 5.0f;
    const int BALL_SIZE = 20;
    float ball_x = WIDTH / 2.0f;
    float ball_y = HEIGHT / 2.0f;
    float ball_velocity_x = 600.0f;
    float ball_velocity_y = 0.0f;
    int paddle_A_points = 0;
    int paddle_B_points = 0;
    const int PADDLE_A_POINTS_X = WIDTH / 3 - (WIDTH * 0.039);
    const int PADDLE_B_POINTS_X = 2 * WIDTH / 3;
    const int PADDLE_POINTS_Y = 15;
    const int FONT_SIZE = 100;

    InitWindow(WIDTH, HEIGHT, "PONG");
    while(!WindowShouldClose()){
        float dt = GetFrameTime();
        if(IsKeyDown(KEY_W)){
            paddle_A_y -= PADDLE_MOVEMENT * dt;
        }
        if(IsKeyDown(KEY_S)){
            paddle_A_y += PADDLE_MOVEMENT * dt;
        }
        if(IsKeyDown(KEY_UP)){
            paddle_B_y -= PADDLE_MOVEMENT * dt;
        }
        if(IsKeyDown(KEY_DOWN)){
            paddle_B_y += PADDLE_MOVEMENT * dt;
        }
        if(paddle_A_y < 0){
            paddle_A_y = 0;
        }
        if(paddle_B_y < 0){
            paddle_B_y = 0;
        }
        if(paddle_A_y > HEIGHT - PADDLE_HEIGHT){
            paddle_A_y = HEIGHT - PADDLE_HEIGHT;
        }
        if(paddle_B_y > HEIGHT - PADDLE_HEIGHT){
            paddle_B_y = HEIGHT - PADDLE_HEIGHT;
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
            ball_velocity_x = 600.0f;
            ball_velocity_y = 0.0f;
            paddle_B_points += 1;
        }
        if(ball_x > WIDTH - BALL_SIZE - 5){
            ball_x = WIDTH / 2.0f;
            ball_y = HEIGHT / 2.0f;
            ball_velocity_x = -600.0f;
            ball_velocity_y = 0.0f;
            paddle_A_points += 1;
        }
        ball_x += ball_velocity_x * dt;
        ball_y += ball_velocity_y * dt;
        BeginDrawing();
        ClearBackground(BG_COLOR);
        Rectangle paddle_A_top = {5, paddle_A_y, PADDLE_WIDTH, PADDLE_HEIGHT / 3};
        Rectangle paddle_A_mid = {5, paddle_A_y + (PADDLE_HEIGHT / 3), PADDLE_WIDTH, PADDLE_HEIGHT / 3};
        Rectangle paddle_A_bot = {5, paddle_A_y + 2 * (PADDLE_HEIGHT / 3), PADDLE_WIDTH, PADDLE_HEIGHT / 3};
        Rectangle paddle_B_top = {WIDTH - 5 - PADDLE_WIDTH, paddle_B_y, PADDLE_WIDTH, PADDLE_HEIGHT / 3};
        Rectangle paddle_B_mid = {WIDTH - 5 - PADDLE_WIDTH, paddle_B_y + (PADDLE_HEIGHT / 3), PADDLE_WIDTH, PADDLE_HEIGHT / 3};
        Rectangle paddle_B_bot = {WIDTH - 5 - PADDLE_WIDTH, paddle_B_y + 2 * (PADDLE_HEIGHT / 3), PADDLE_WIDTH, PADDLE_HEIGHT / 3};
        Rectangle ball = {ball_x, ball_y, BALL_SIZE, BALL_SIZE};
        if(CheckCollisionRecs(ball, paddle_A_top) || (CheckCollisionRecs(ball, paddle_A_mid) || CheckCollisionRecs(ball, paddle_A_bot))){
            ball_velocity_x *= -1;
            ball_x = 5 + PADDLE_WIDTH;
        }
        if(CheckCollisionRecs(ball, paddle_B_top) || (CheckCollisionRecs(ball, paddle_B_mid) || CheckCollisionRecs(ball, paddle_B_bot))){
            ball_velocity_x *= -1;
            ball_x = WIDTH - 5 - PADDLE_WIDTH - BALL_SIZE;
        }
        if(CheckCollisionRecs(ball, paddle_A_top) || CheckCollisionRecs(ball, paddle_B_top)){
            ball_velocity_y = -PADDLE_BOUNCE;
        }
        if(CheckCollisionRecs(ball, paddle_A_mid) || CheckCollisionRecs(ball, paddle_B_mid)){
            ball_velocity_y = 0;
        }
        if(CheckCollisionRecs(ball, paddle_A_bot) || CheckCollisionRecs(ball, paddle_B_bot)){
            ball_velocity_y = PADDLE_BOUNCE;
        }
        DrawRectangleRec(paddle_A_top, FG_COLOR);
        DrawRectangleRec(paddle_A_mid, FG_COLOR);
        DrawRectangleRec(paddle_A_bot, FG_COLOR);
        DrawRectangleRec(paddle_B_top, FG_COLOR);
        DrawRectangleRec(paddle_B_mid, FG_COLOR);
        DrawRectangleRec(paddle_B_bot, FG_COLOR);
        DrawRectangleRec(ball, FG_COLOR);
        DrawRectangle((WIDTH / 2) - (HALFLINE_WIDTH / 2), 0, HALFLINE_WIDTH, HEIGHT, FG_COLOR);
        DrawText(TextFormat("%d", paddle_A_points), PADDLE_A_POINTS_X, PADDLE_POINTS_Y, FONT_SIZE, FG_COLOR);
        DrawText(TextFormat("%d", paddle_B_points), PADDLE_B_POINTS_X, PADDLE_POINTS_Y, FONT_SIZE, FG_COLOR);
        EndDrawing();
    };
    CloseWindow();

    return 0;
}
