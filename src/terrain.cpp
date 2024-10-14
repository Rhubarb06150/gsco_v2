/*
/src/terrain.cpp

manage terrain, show it and control it
*/
#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include<filesystem>
#include<string.h>
#include<fstream>
#include<iostream>
#include<chrono>
#include<unistd.h>

#include"headers/camera.hpp"
#include"headers/console.hpp"
#include"headers/hud.hpp"
#include"headers/player.hpp"
#include"headers/window.hpp"
#include"headers/engine.hpp"

std::vector<std::vector<sf::Texture>> terrain_textures={{},{},{}};
std::vector<std::vector<std::string>> terrain_textures_indexes={};
std::vector<std::vector<std::string>> terrain_vector={};

unsigned int time_otd=0;
unsigned int hovering_tile=1;
int scanline_l=0;
int scanline_t=0;
unsigned int tiles_nb_h=(resolution_h/16)+2;
unsigned int tiles_nb_v=(resolution_v/16)+2;
int showed_tiles=0;
int t_vector_size=0;

int get_tile_index(std::string tile){
	for(int i=0;i<terrain_textures_indexes.size();i++){
		if(terrain_textures_indexes[i][1]==tile)
		return i;
	};
	return 0;
}

void init_terrain(){
	terrain_textures_indexes={};
	terrain_vector={};
	terrain_textures_indexes.push_back({"grass","\x00"});
	terrain_textures_indexes.push_back({"bush","\x01"});
	terrain_textures_indexes.push_back({"little_tree","\x02"});
	terrain_textures_indexes.push_back({"clean_tall_grass","\x03"});
	sf::Texture texture;
	for(int i=0;i<terrain_textures_indexes.size();i++){
		texture.loadFromFile("assets/graphics/terrain/m"+terrain_textures_indexes[i][0]+".png");
		terrain_textures[0].push_back(texture);
		texture.loadFromFile("assets/graphics/terrain/d"+terrain_textures_indexes[i][0]+".png");
		terrain_textures[1].push_back(texture);
		texture.loadFromFile("assets/graphics/terrain/n"+terrain_textures_indexes[i][0]+".png");
		terrain_textures[2].push_back(texture);
	};
	int size_x=256;
	int size_y=256;
	for(int y=0;y<size_y;y++){
		terrain_vector.push_back({});
		for(int x=0;x<size_x;x++){
			terrain_vector[y].push_back(terrain_textures_indexes[rand()%terrain_textures.size()][1]);
			/*
			if(x==0||y==0||x==(size_x-1)||y==(size_y-1)){
				terrain_vector[y].push_back(terrain_textures_indexes[1][1]);
			}else{
				terrain_vector[y].push_back(terrain_textures_indexes[0][1]);
			}
			*/
		};
	};
	t_vector_size=terrain_vector.size();
};

void show_terrain(){
	std::string last_tile="\0";
	int b_pos_x=player_pos_x/16;
	int b_pos_y=player_pos_y/16;
	showed_tiles=0;
	sf::Sprite terrain_tile; //master tile

	scanline_l=/*(camera_x/16)+*/b_pos_x;
	scanline_t=/*(camera_y/16)+*/b_pos_y;
	scanline_l-=(tiles_nb_h/2)-1;
	scanline_t-=((tiles_nb_v-2)/2)+1;

	if(scanline_l<0)
		scanline_l=0;
	if(scanline_t<0)
		scanline_t=0;
	fflush(stdout);
	for(int y=scanline_t;y<(scanline_t+tiles_nb_v);y++){
		int cur_t_line_size=terrain_vector[y].size();
		if((y*16)+camera_y-player_pos_y>resolution_v||y>=t_vector_size||(y-scanline_t)>tiles_nb_v){
			break;
		}
		for(int x=scanline_l;x<(scanline_l+tiles_nb_h);x++){
			if((x*16)+camera_x-player_pos_x>resolution_h||x>=cur_t_line_size||(x-scanline_l)>tiles_nb_h)
				break;
			terrain_tile.setPosition(
			((x*16)+camera_x-player_pos_x),
			((y*16)+camera_y-player_pos_y)
			);
			if(last_tile!=terrain_vector[y][x]){
				terrain_tile.setTexture(terrain_textures[time_otd][get_tile_index(terrain_vector[y][x])]);
			}
			last_tile=terrain_vector[y][x];
			window.draw(terrain_tile);
			showed_tiles++;
			//update_window();
			//usleep(25000);
		}
	}
	//DEBUG
	//show_text(std::to_string(scanline_l)+","+std::to_string(scanline_t),0,0);
	//show_text("tiles:"+std::to_string(showed_tiles),0,8);
	
	//show_text("scanline_l: "+std::to_string(scanline_l)+"\nscanline_t: "+std::to_string(scanline_t),0,0);
	//show_text("posx: "+std::to_string(player_pos_x)+"\nposy: "+std::to_string(player_pos_y),0,16);
	//show_text("tiles:"+std::to_string(showed_tiles),0,8);
	//show_text("ar: "+aspect_ratio,0,40);
};

void load_map_from_file(std::string map_path){
	if(std::filesystem::exists(map_path)){
		//printf("Map exists!");
		std::ifstream map_file(map_path);
		std::string cur_line;

		//Map values
		std::string map_name;
		std::string map_desc;
		std::string map_width;
		std::string map_height;
		std::string default_tile;

		while(std::getline(map_file,cur_line)){
			//cur_line=replace_str(cur_line,"\n","");
			//std::cout<<cur_line<<std::endl;
			if(str_starts(cur_line,"#NAME:")){
				cur_line=replace_str(cur_line,"#NAME:","");
				map_name=cur_line;
			}else if(str_starts(cur_line,"#DESC:")){
				cur_line=replace_str(cur_line,"#DESC:","");
				map_desc=cur_line;
			}else if(str_starts(cur_line,"#DEFAULT:")){
				cur_line=replace_str(cur_line,"#DEFAULT:","");
				default_tile=cur_line;
			}else if(str_starts(cur_line,"#DIMS:")){
				std::cout<<"FIND DIMS"<<std::endl;
				cur_line=replace_str(cur_line,"#DIMS:","");
				bool mes_width=true;
				for(int i=0;i<cur_line.length();i++){
					std::string cur_char;
					std::cout<<"CHAR:"<<cur_char<<std::endl;
					cur_char=cur_line[i];
					if(mes_width){
						if(cur_char!=","){
							map_width.append(cur_char);
						}else{
							mes_width=false;
						}
					}else{
						map_height.append(cur_char);
					}
				}
			}else if(str_starts(cur_line,"#STPOS:")){
				cur_line=replace_str(cur_line,"#STPOS:","");
				//map_name=cur_line;
			}
			std::cout<<"map name:"<<map_name<<std::endl;
			std::cout<<"map desc:"<<map_desc<<std::endl;
			std::cout<<"map width:"<<map_width<<"|"<<std::endl;
			std::cout<<"map height:"<<map_height<<"|"<<std::endl;
			std::cout<<"default tile:"<<default_tile<<std::endl;
			terrain_vector={};
			int r_map_width;
			r_map_width=stoi(map_width);
			int r_map_height;
			r_map_height=stoi(map_height);
			for(int y=0;y<r_map_height;y++){
				for(int x=0;x<r_map_width;x++){
					terrain_vector[y][x]=default_tile;
				}
			}
		}
	}else{
		log("ERROR","Cannot load the map!");
	}
};
