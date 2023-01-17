#ifndef tetrisGame_h

void game_over();
void game_loop();
void display();
bool new_block();
void init_game();
void move_block(uint8_t, uint8_t);
void copy_field();
bool check_collide(uint8_t, uint8_t);
bool rotate_block();
void game();
void line_check();
void line_erase(uint8_t);

void clear_display();
void clear_all();
void buttons_control();

void set_pixel(uint8_t, uint8_t);
void clear_pixel(uint8_t, uint8_t);

#endif