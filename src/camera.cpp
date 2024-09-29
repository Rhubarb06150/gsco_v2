#include"headers/camera.hpp"
#include"headers/window.hpp"
int camera_x=(resolution_h/2)+16;
int camera_y=resolution_v/2;

void reset_camera(){
	camera_x=(resolution_h/2)-16;
	camera_y=resolution_v/2;

};
