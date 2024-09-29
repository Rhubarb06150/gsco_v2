/*
/src/window.cpp

manage window, and the resolution
*/
#include<SFML/Graphics.hpp>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include<cmath>
#include"headers/window.hpp"
#include"headers/engine.hpp"
#include"headers/console.hpp"
sf::RenderWindow window;

//10:9 160x144
//5:4  180x144
//4:3  192x144
//16:9 256x144

int resolution_h=160;
int resolution_v=144;
int win_width=resolution_h*2;
int win_height=resolution_v*2;
int frame_drawn=0;
std::string aspect_ratio;

void init_window(){
	float ar=0.0;
	ar=(float(resolution_h)/resolution_v);
	int rar;
	rar=ar*1000;
	if(rar==1250){
		aspect_ratio="5:4";
	}else if(rar==1333){
		aspect_ratio="4:3";
	}else if(rar==1111){
		aspect_ratio="10:9";
	}else if(rar==1777){
		aspect_ratio="16:9";
	}else{
		aspect_ratio=UNKNOWN;
	}
	sf::VideoMode win_size(resolution_h,resolution_v);
	window.create(win_size,"GSC Online");
	//window.setFramerateLimit(60);
	log("WINDOW","Window created. - Resolution: "+std::to_string(resolution_h)+"x"+std::to_string(resolution_v)+" - Aspect ratio: "+aspect_ratio);
}

void update_window(){
	window.display();
}

void clear_window(){
	window.clear();
}

void set_bg(int r,int g,int b){
	window.clear(sf::Color(r,g,b));
}

void update_window_values(){

}