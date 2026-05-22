#include "raylib.h"
#include "paddle.hpp"

void Paddle::set_pos(Vector2 new_pos) {
    this->pos = new_pos;
}

void Paddle::update(float delta_time, int window_width, int window_height) {
    if (!this->is_ai) {
        if (IsKeyDown(KEY_S)) {
            this->pos.y += this->move_speed * delta_time;
        } else if (IsKeyDown(KEY_W)) {
            this->pos.y -= this->move_speed * delta_time;
        }
    } else {
        this->pos.y = this->alternative_y;
    }
    if (this->pos.y <= 0)
        this->pos.y = 0;
    else if (this->pos.y >= window_height - this->height)
        this->pos.y = window_height - this->height;
}

void Paddle::render() {
    DrawRectangle(this->pos.x, this->pos.y, this->dimensions.x, this->dimensions.y, RAYWHITE);
}

Vector2 Paddle::get_pos() const {
    return this->pos;
}

Vector2 Paddle::get_dimensions() const {
    return this->dimensions;
}

bool Paddle::check_if_ai() const {
    return this->is_ai;
}
