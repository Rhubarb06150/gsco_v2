#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

extern std::vector<sf::Texture> terrain_textures;
extern std::vector<std::string> terrain_textures_indexes;
extern std::vector<std::string> terrain_vector;
extern unsigned int time_otd;
extern unsigned int hovering_tile;

void init_terrain();
void show_terrain();
void load_map_from_file(std::string map_path);

#endif
