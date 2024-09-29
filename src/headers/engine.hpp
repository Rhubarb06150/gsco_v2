#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <SFML/Graphics.hpp>
#include <chrono>
#include <string>

extern int frames;
extern int win_width;
extern int win_height;
extern sf::Event event;
extern sf::Clock game_clock;
extern float fps;
extern std::chrono::high_resolution_clock::time_point time_start;
extern std::chrono::high_resolution_clock::time_point time_end;
extern const char* UNKNOWN;
extern std::string user_path;

void init_engine();
void frame();
void begin_fps_measure();
void end_fps_measure();
void screenshot();
int create_missing_dir(std::string path);
bool str_starts(std::string str,std::string pattern);
std::string replace_str(std::string str,const std::string& from,const std::string& to);
#endif
