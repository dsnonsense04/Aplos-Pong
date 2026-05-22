#include <iostream>
#include "raylib.h"
#include "ball.hpp"

void Ball::update(float delta_time, int window_width, int window_height) {
    this->pos.x += this->vel.x * delta_time;
    this->pos.y += this->vel.y * delta_time;
    if (this->pos.y <= 0 || this->pos.y >= window_height - this->radius)
        this->vel.y *= -1;    
}

void Ball::render() {
    DrawRectangle(this->pos.x, this->pos.y, this->radius, this->radius, this->colour);
}

void Ball::set_pos(Vector2 new_pos) {
    this->pos = new_pos;
}

void Ball::set_vel(Vector2 new_vel) {
    this->vel = new_vel;
}

int Ball::get_radius() const {
    return this->radius;
}

Vector2 Ball::get_pos() const {
    return this->pos;
}

Vector2 Ball::get_vel() const {
    return this->vel;
}
