#include"headers/engine.hpp"
#include"headers/window.hpp"
#include"headers/player.hpp"
#include"headers/terrain.hpp"
#include"headers/hud.hpp"
#include"headers/console.hpp"
#include"headers/camera.hpp"
#include<filesystem>
#include<cstring>
#include<chrono>
#include<algorithm>
#include<string>
#include<SFML/Graphics.hpp>
#include<thread>
#include<unistd.h>
#ifdef __linux__
	#include<sys/types.h>
	#include<pwd.h>
#endif

int frames;
sf::Event event;
sf::Clock game_clock;
const char* UNKNOWN="<?>";
float fps=0;
std::chrono::high_resolution_clock::time_point time_start;
std::chrono::high_resolution_clock::time_point time_end;
std::string user_path="";

void init_engine(){
	#ifdef _WIN32
		user_path=getenv("APPDATA");
	#elif __linux__
		struct passwd* pw=getpwuid(getuid());
		user_path=pw->pw_dir;
	#endif
}
void begin_fps_measure(){
	time_start=std::chrono::high_resolution_clock::now();
}
void end_fps_measure(){
	time_end=std::chrono::high_resolution_clock::now();
	fps=(float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(time_end-time_start).count();
}
void screenshot(){
	create_missing_dir(user_path+"/.gsc_o");
	create_missing_dir(user_path+"/.gsc_o/screenshots");
	sf::Texture tx;
	tx.create(window.getSize().x,window.getSize().y);
	tx.update(window);
	time_t now=time(NULL);
	struct tm *tm_struct=localtime(&now);
	int cur_hour=tm_struct->tm_hour;
	int cur_mins=tm_struct->tm_min;
	int cur_secs=tm_struct->tm_sec;
	char cur_h_str[3];
	char cur_m_str[3];
	char cur_s_str[3];
	sprintf(cur_h_str,"%ld",cur_hour);
	sprintf(cur_m_str,"%ld",cur_mins);
	sprintf(cur_s_str,"%ld",cur_secs);
	char hour[3]="";
	char mins[3]="";
	char secs[3]="";
	if(cur_hour<10){strcpy(hour,"0");};strcat(hour,cur_h_str);
	if(cur_mins<10){strcpy(mins,"0");};strcat(mins,cur_m_str);
	if(cur_secs<10){strcpy(secs,"0");};strcat(secs,cur_s_str);
	std::string screen_name;
	screen_name="gsco_"+std::string(hour)+"_"+std::string(mins)+"_"+std::string(secs)+".png";
	if(tx.copyToImage().saveToFile(user_path+"/.gsc_o/screenshots/"+screen_name)){
		log("INFO","Screenshot saved at "+screen_name);
	}else{
		log("ERROR","Failed to save screenshot at "+screen_name);
	}
}
int create_missing_dir(std::string path){
	if(std::filesystem::is_regular_file(path)){
		return 1;
	}else if(std::filesystem::is_directory(path)){
		return 0;
	}else{
		std::string command;
		command="mkdir "+path;
		system(command.c_str());
		return 0;
	}
}

void frame(){
	//printf("Frame: %d\n",frames);
	frames++;
	sf::Event event;
	while(window.pollEvent(event)){
		//PLAYER
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			player_pos_x+=4;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(player_pos_x>0)
				player_pos_x-=4;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			if(player_pos_y>0)
				player_pos_y-=4;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			player_pos_y+=4;
		}
		//CAMERA
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
			camera_x+=4;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
			camera_x-=4;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
			camera_y-=4;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
			camera_y+=4;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)){
			screenshot();
		}else if(event.type==sf::Event::Closed){
			window.close();
			exit(0);
		}else if(event.type==sf::Event::KeyPressed){
			if(event.key.code==sf::Keyboard::F11){
				sf::VideoMode desktop=sf::VideoMode::getDesktopMode();
				window.create(sf::VideoMode(160,144),"WIN",sf::Style::Fullscreen);
			}else if(event.key.code==sf::Keyboard::M){
				time_otd=0;
			}else if(event.key.code==sf::Keyboard::D){
				time_otd=1;
			}else if(event.key.code==sf::Keyboard::N){
				time_otd=2;
			};;
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)&&sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Add){
			win_width+=resolution_h;
			win_height+=resolution_v;
			//printf("zoom in\n");
			//fflush(stdout);
			window.setSize(sf::Vector2u(win_width,win_height));
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)&&sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Subtract){
			if(win_width>resolution_h){
				win_width-=resolution_h;
				win_height-=resolution_v;
			};
			//printf("zoom out\n");
			//fflush(stdout);
			window.setSize(sf::Vector2u(win_width,win_height));
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)&&sf::Event::KeyPressed&&event.key.code==sf::Keyboard::R){
			set_text_color(rand()%255,rand()%255,rand()%255,255);
			printf("random text color\n");
			fflush(stdout);
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)&&sf::Event::KeyPressed&&event.key.code==sf::Keyboard::F){
			colored_letters_textures={};
			colored_letters_indexes={};
			log("ENGINE","Memory flushed!");
		}
	}
}

bool str_starts(std::string str,std::string pattern){
	if(str.rfind(pattern,0)==0){
		return true;
	}else{
		return false;
	}
}

std::string replace_str(std::string str,const std::string& from,const std::string& to){
	size_t spos=0;
	while((spos=str.find(from,spos))!=std::string::npos){
		str.replace(spos,from.length(),to);
		spos+=to.length();
	}
	return str;
}
