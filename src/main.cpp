#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>

#include "headers/console.hpp"
#include "headers/camera.hpp"
#include "headers/window.hpp"
#include "headers/engine.hpp"
#include "headers/terrain.hpp"
#include "headers/player.hpp"
#include "headers/hud.hpp"
#include "headers/texts.hpp"
#include "headers/infos.h"

int main(){

	//show_text("gsco v"+std::string(VERSION),0,0);
	//update_window();
	reset_camera();

	init_engine();
	//show_text("engine started"+std::string(VERSION),0,8);
	//update_window();

	hud_init();
	log("HUD","HUD loaded.");
	//show_text("HUD loaded"+std::string(VERSION),0,16);
	//update_window();

	init_terrain();
	log("TERRAIN","Terrain loaded.");
	//show_text("terrain loaded"+std::string(VERSION),0,24);
	//update_window();
	init_window();

	

	//load_map_from_file("maps/map1.lv");

	while(true){
		frame_drawn=0;
		//if(frames%2==0){
			begin_fps_measure();
		//};
		clear_window();
		show_terrain();

		/*
		show_text("gsco v"+std::string(VERSION),0,0);

		char aspect[12];
		sprintf(aspect,"ratio:%s",ASPECT_RATIO);
		show_text_c(aspect,0,16);

		char frames_char[20];
		sprintf(frames_char,"frames:$%x",frames);
		show_text_c(frames_char,0,8);

		char pos[16];
		sprintf(pos,"x:$%x\ny:$%x",player_pos_x/16,player_pos_y/16);
		show_text_c(pos,0,24);

		char r_pos[16];
		sprintf(r_pos,"Rx:$%x\nRy:$%x",player_pos_x,player_pos_y);
		show_text_c(r_pos,0,40);
		*/
		//char camera[16];
		//sprintf(camera,"cmx:%d\ncmy:%d",camera_x,camera_y);
		//show_text(camera,0,56);
		

		//draw_square(0,(resolution_v/8)-5,resolution_h/8,5);
		//show_text("ATTEND QUOI????",8,112);
		frame();
		//show_text("frames:"+std::to_string(frames),0,0);
		update_window();
		frame_drawn=1;
		//if(frames%2==0){
			//end_fps_measure();
		//};
	};
	exit(0);
	return 0;
};
