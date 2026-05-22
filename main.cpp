#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "raylib.h"

#include "paddle.hpp"
#include "ball.hpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int player_score = 0;
std::string player_score_str = std::to_string(player_score);
int ai_score = 0;
std::string ai_score_str = std::to_string(ai_score);

Ball ball(WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - 20, 20, RAYWHITE);
Paddle paddle_player(25, WINDOW_HEIGHT / 2 - 120, RAYWHITE);
Paddle paddle_ai(WINDOW_WIDTH - 100, WINDOW_HEIGHT / 2 - 120, RAYWHITE, ball.get_pos().y, false);

bool can_play_sound = true;

void draw_net() {
    for (int i = 0; i < WINDOW_HEIGHT; i += 32) {
        DrawRectangle(WINDOW_WIDTH / 2 - 25, i, 25, 20, LIGHTGRAY);
    }
}

void randomize_position() {
    const int RAND_MODIFIER = 100;
    const int HALF_RAND_MOD = RAND_MODIFIER / 2;
    int rand_num = (rand() % RAND_MODIFIER) + 1;

    if (rand_num >= HALF_RAND_MOD)
        ball.set_vel({-150, 150});
    else if (rand_num <= HALF_RAND_MOD)
        ball.set_vel({150, -150});
}

void calculate_scores(Sound sound) {
    if (ball.get_pos().x <= 0) {
        ball.set_pos({WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - 20});
        
        player_score++;
        player_score_str = std::to_string(player_score);
        
        PlaySound(sound);
        randomize_position();
    } else if (ball.get_pos().x >= WINDOW_WIDTH) {
        ball.set_pos({WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - 20});
        
        ai_score++;
        ai_score_str = std::to_string(ai_score);
    
        PlaySound(sound);
        randomize_position();
    }
}

void check_collisions(Paddle& paddle, Ball& ball, Sound sound) {
    Rectangle paddle_rect = {
        paddle.get_pos().x,
        paddle.get_pos().y,
        paddle.get_dimensions().x,
        paddle.get_dimensions().y
    };
    Rectangle ball_rect = {
        ball.get_pos().x,
        ball.get_pos().y,
        ball.get_radius(),
        ball.get_radius()
    };
    bool has_collided = CheckCollisionRecs(paddle_rect, ball_rect);
    if (has_collided && can_play_sound) {
        PlaySound(sound);
        Vector2 vel = ball.get_vel();
        vel.x *= -1;
        ball.set_vel(vel);
        can_play_sound = false;
    } else if (!has_collided) {
        can_play_sound = true;
    }
}

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Simple Pong");
    InitAudioDevice();
    SetTargetFPS(60);

    srand(time(NULL));

    player_score_str = std::to_string(player_score);
    ai_score_str = std::to_string(ai_score);
    
    Sound paddle_collision = LoadSound("collideWithPaddle.wav");
    Sound score = LoadSound("score.wav");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            
            draw_net();
            calculate_scores(score);
            check_collisions(paddle_player, ball, paddle_collision);
            check_collisions(paddle_ai, ball, paddle_collision);

            ball.update(GetFrameTime(), WINDOW_WIDTH, WINDOW_HEIGHT);
            ball.render();
            
            paddle_player.update(GetFrameTime(), WINDOW_WIDTH, WINDOW_HEIGHT);
            paddle_ai.update(GetFrameTime(), WINDOW_WIDTH, WINDOW_HEIGHT);
            paddle_player.render();
            paddle_ai.render();
            paddle_ai.set_pos({ WINDOW_WIDTH - 40, ball.get_pos().y - 60 });


            DrawText(player_score_str.c_str(), WINDOW_WIDTH / 2 - 100, 50, 55, RAYWHITE);
            DrawText(ai_score_str.c_str(), WINDOW_WIDTH / 2 + 50, 50, 55, RAYWHITE);
        EndDrawing();
    }

    UnloadSound(paddle_collision);
    UnloadSound(score);
    CloseAudioDevice();
    CloseWindow();
    return EXIT_SUCCESS;
}
