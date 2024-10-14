// /src/hud.cpp - Gestion of the hud and texts on the screen

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

#include "headers/window.hpp"
#include "headers/engine.hpp"
#include "headers/texts.hpp"
#include "headers/terrain.hpp"


std::vector<std::vector<sf::Texture>> letters={};
std::vector<sf::Texture> colored_letters_textures={};
std::vector<std::string> colored_letters_indexes={};
std::vector<unsigned int> text_color={0,0,0,255};
std::vector<unsigned int> text_bg_color={255,255,255,255};

//PRIV
std::vector<std::vector<sf::Texture>> borders;

int border_style=6;

void hud_init(){
	sf::Texture l;
	l.loadFromFile("assets/graphics/hud/font.png",sf::IntRect(24,120,8,8));
	for(int i=0;i<16;i++){
		letters.push_back({l,l,l,l,l,l,l,l,l,l,l,l,l,l,l,l});
	};
	std::string toc=" 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz:;.!?_-/\\()[]}{<>\"'$#|";
	for(int i=0;i<toc.size();i++){
		unsigned int h_v=int(toc[i]);
		unsigned int x=h_v/16;
		unsigned int y=h_v%16;
		//printf("Letter: %c,x: %d,y: %d\n",toc[i],x,y);
		sf::Texture letter_texture;
		letter_texture.loadFromFile("assets/graphics/hud/font.png",sf::IntRect(x*8,y*8,8,8));
		letters[y][x]=letter_texture;
	};
	for(int i=0;i<11;i++){
		borders.push_back({});
		l.loadFromFile("assets/graphics/hud/border.png",sf::IntRect(0,(i*16)+0,8,8));//corner top left
		borders[i].push_back(l);
		l.loadFromFile("assets/graphics/hud/border.png",sf::IntRect(8,(i*16)+0,8,8));//horizontal
		borders[i].push_back(l);
		l.loadFromFile("assets/graphics/hud/border.png",sf::IntRect(16,(i*16)+0,8,8));//corner top right
		borders[i].push_back(l);
		l.loadFromFile("assets/graphics/hud/border.png",sf::IntRect(0,(i*16)+8,8,8));//vertical
		borders[i].push_back(l);
		l.loadFromFile("assets/graphics/hud/border.png",sf::IntRect(8,(i*16)+8,8,8));//corner bottom left
		borders[i].push_back(l);
		l.loadFromFile("assets/graphics/hud/border.png",sf::IntRect(16,(i*16)+8,8,8));//corner bottom right
		borders[i].push_back(l);
	}
}

void show_text(std::string text,int xpos,int ypos){
	unsigned int x_pos=xpos;
	unsigned int y_pos=ypos;
	bool colored=false;
	if(sf::Color(text_color[0],text_color[1],text_color[2],text_color[3])!=sf::Color(0,0,0,255)){
		colored=true;
	};
	sf::Sprite cur_letter;
	for(int i=0;i<text.size();i++){
		if(text[i]=='\n'){
			x_pos=xpos;
			y_pos+=8;
		}else{
			//sf::Sprite cur_letter;
			unsigned int h_v=int(text[i]);
			unsigned int x=h_v/16;
			unsigned int y=h_v%16;
			//sf::Texture letter_texture=letters[y][x];
			if(colored){
				std::string index;
				index=text[i];
				index+=std::to_string(text_color[0])+","+std::to_string(text_color[1])+","+std::to_string(text_color[2])+","+std::to_string(text_color[3]);
				if(std::find(colored_letters_indexes.begin(),colored_letters_indexes.end(),index)!=colored_letters_indexes.end()){
					//COLOR REGISTERED.
					for(int j=0;j<colored_letters_indexes.size();j++){
						if(index==colored_letters_indexes[j]){
							cur_letter.setTexture(colored_letters_textures[j]);
							break;
						};
					};
				}else{
					sf::Texture letter_texture=letters[y][x];
					//COLOR NOT REGISTERED YET.
					sf::Image letter_texture_img=letter_texture.copyToImage();
					if(sf::Color(text_color[0],text_color[1],text_color[2],text_color[3])!=sf::Color(0,0,0,255)){
						for(int texture_x=0;texture_x<8;texture_x++){
							for(int texture_y=0;texture_y<8;texture_y++){
								sf::Color pix;
								pix=letter_texture_img.getPixel(texture_x,texture_y);
								if(pix==sf::Color(0,0,0,255)){
									letter_texture_img.setPixel(texture_x,texture_y,sf::Color(text_color[0],text_color[1],text_color[2],text_color[3]));
								};
							};
						};
						//printf("Registered the letter %c, with color R:%dG:%dB:%dA:%d\n",text[i],text_color[0],text_color[1],text_color[2],text_color[3]);
						//fflush(stdout);
						colored_letters_indexes.push_back(index);
						letter_texture.loadFromImage(letter_texture_img);
						colored_letters_textures.push_back(letter_texture);
					};
				};
			};
			if(!colored){
				cur_letter.setTexture(letters[y][x]);
			};
			cur_letter.setPosition(x_pos,y_pos);
			window.draw(cur_letter);
			x_pos+=8;
		};
	};
}

void draw_square(unsigned int x,unsigned int y,unsigned int size_x,unsigned int size_y){
	x=x*8;
	y=y*8;
	sf::Sprite cur_border_tile;
	for(int i=0;i<size_x;i++){
		for(int j=0;j<size_y;j++){
			if(i==0&&j==0){
				cur_border_tile.setTexture(borders[border_style][0]);//corner   top   left
			}else if(i==(size_x-1)&&j==(size_y-1)){
				cur_border_tile.setTexture(borders[border_style][5]);//corner bottom right
			}else if(j==(size_y-1)&&i==0){
				cur_border_tile.setTexture(borders[border_style][4]);//corner bottom  left
			}else if(j==0&&i==(size_x-1)){
				cur_border_tile.setTexture(borders[border_style][2]);//corner  top   right
			}else if(i==0||i==(size_x-1)){
				cur_border_tile.setTexture(borders[border_style][3]);//vertical
			}else if(j==0||j==(size_y-1)){
				cur_border_tile.setTexture(borders[border_style][1]);//vertical
			}else{
				cur_border_tile.setTexture(letters[0][2]);//vertical
			}
			cur_border_tile.setPosition(x+(i*8),y+(j*8));
			window.draw(cur_border_tile);
		}
	}
}

void set_text_color(unsigned int r,unsigned int g,unsigned int b,unsigned int a){
	text_color={r,g,b,a};
}

void reset_text_color(){
	text_color={0,0,0,255};
}

void show_text_c(char* text,int xpos,int ypos){
	std::string to_p;
	to_p=text;
	show_text(to_p,xpos,ypos);
}

int ask_yn(std::string question){
	unsigned int choice=0;
	draw_square(0,13,24,5);
	show_text(question,8,112);
	draw_square(18,10,6,4);
	show_text(texts["no"][user_lang]+"\n"+texts["yes"][user_lang],160,88);
	show_text("|",152,88+(choice*8));
	update_window();
	while(true){
		//frame();
		sf::Event event;
		while(window.pollEvent(event)){
			//if(event.type==sf::Event::KeyPressed){
				//if(event.key.code==sf::Keyboard::Up||event.key.code==sf::Keyboard::Down){
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
					if(choice==0){
						choice=1;
					}else{
						choice=0;
					}
					//std::cout<<"choice"<<std::endl;
					draw_square(18,10,6,4);
					show_text("|",152,88+(choice*8));
					show_text(texts["no"][user_lang]+"\n"+texts["yes"][user_lang],160,88);
					update_window();
				}else if(event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Return){
					return choice;
				}
				//frame_eng();
			}
		//}
		//update_window();
		//update_window();
	}
}