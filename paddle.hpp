#include "raylib.h"

class Paddle {
    public:
        Paddle(int x, int y, Color colour, int alternative_y = 0, bool is_ai = false)
            : x(x), y(y), colour(colour), alternative_y(alternative_y), is_ai(is_ai) {
                this->pos = (Vector2) { this->x, this->y };
                this->move_speed = 250;
                this->width = 25;
                this->height = 120;
                this->dimensions = (Vector2) { this->width, this->height };
            }

        void update(float delta_time, int window_width, int window_height);
        void render();

        void set_pos(Vector2 new_pos);
        Vector2 get_pos() const;
        Vector2 get_dimensions() const;
        bool check_if_ai() const;

    private:
        Vector2 pos;
        Vector2 dimensions;
        int width; 
        int height;
        int x; int y;
        int alternative_y;
        int move_speed;
        Color colour;
        bool is_ai;
};