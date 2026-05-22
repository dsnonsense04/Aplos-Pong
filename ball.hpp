#include "raylib.h"

class Ball {
    public:
        Ball(int x, int y, int radius, Color colour)
            : x(x), y(y), radius(radius), colour(colour) {
                this->x_speed = 150;
                this->y_speed = 150;
                this->pos = (Vector2) { x, y };
                this->vel = (Vector2) { x_speed, y_speed };
            }

        void update(float delta_time, int window_width, int window_height);
        void render();

        void set_pos(Vector2 new_pos);
        void set_vel(Vector2 new_vel);
        int get_radius() const;
        Vector2 get_pos() const;
        Vector2 get_vel() const;

    private:
        Vector2 pos;
        Vector2 vel;
        int x; int y;
        int x_speed;
        int y_speed;
        int radius;
        Color colour;
};