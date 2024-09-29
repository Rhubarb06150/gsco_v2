#ifndef HUD_HPP
#define HUD_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

extern std::vector<sf::Sprite> letters;
extern std::vector<unsigned int> text_color;
extern std::vector<unsigned int> text_bg_color;
extern std::vector<sf::Texture> colored_letters_textures;
extern std::vector<std::string> colored_letters_indexes;
extern int border_style;

void hud_init();
void show_text(std::string text,int xpos, int ypos);
void show_text_c(char* text,int xpos, int ypos);
void set_text_color(unsigned int r,unsigned int g,unsigned int b,unsigned int a);
void reset_text_color();
void draw_square(unsigned int x,unsigned int y,unsigned int size_x,unsigned int size_y);

#endif
