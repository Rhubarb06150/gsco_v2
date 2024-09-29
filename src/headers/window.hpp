#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern int resolution_h;
extern int resolution_v;
extern int win_width;
extern int win_height;
extern std::string aspect_ratio;
extern int frame_drawn;

void init_window();
void clear_window();
void update_window();
void set_bg(int r,int g,int b);
void update_window_values();

#endif
