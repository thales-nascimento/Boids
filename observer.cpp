#include "observer.hpp"

#define FREE_CAMERA 0
#define THIRD_UP 1
#define GEO_ESTACIONARIA 2
#define OBSERVER_SPEED 8

Planeta *planeta;

bool observer_pause=false;
int modo_observacao = FREE_CAMERA;
unsigned int id_observado=0;

double theta_geoestacionaria = 0;
double theta_free=0, phi_free=0;
float distancia_geoestacionaria=RAIO_TERRA+1000;

Vetor posicao_observador;

void observer_look(){
	switch(modo_observacao){
		case FREE_CAMERA:{
			double cosphi = cos(phi_free);
			double abscosphi = cosphi<0?-cosphi:cosphi;
			
			gluLookAt(posicao_observador.x,posicao_observador.y,posicao_observador.z,
					posicao_observador.x+abscosphi*cos(theta_free), posicao_observador.y+sin(phi_free), posicao_observador.z+abscosphi*sin(theta_free),
					cos(phi_free+PI/2)*cos(theta_free),cos(phi_free),cos(phi_free+PI/2)*sin(theta_free) );
			break;
		}
		case THIRD_UP:{			
			
		}
		case GEO_ESTACIONARIA:{
			double rotacao = planeta->get_rotation();
			Vetor posicao_observador(distancia_geoestacionaria*cos(rotacao + theta_geoestacionaria),0,distancia_geoestacionaria*sin(rotacao + theta_geoestacionaria));
			
			double y,z;
			y = cos(-planeta->INCLINACAO_ROT)*posicao_observador.y - sin(-planeta->INCLINACAO_ROT)*posicao_observador.z;
			z = sin(-planeta->INCLINACAO_ROT)*posicao_observador.y - cos(-planeta->INCLINACAO_ROT)*posicao_observador.z;
			posicao_observador.y = y;
			posicao_observador.z = z;
			
			Vetor centro = planeta->get_coordenadas();
			posicao_observador += centro;
			
			gluLookAt(posicao_observador.x,posicao_observador.y,posicao_observador.z,
					centro.x,centro.y,centro.z,
					0,cos(planeta->INCLINACAO_ROT),sin(planeta->INCLINACAO_ROT));
			break;
			break;
		}
	}
	
	glutPostRedisplay();
}

void keyboard_free_camera(unsigned char key,int x, int y){
	switch(key){
		case 'p': observer_pause = !observer_pause;
		break;
		case 'w':{
			posicao_observador.z+=OBSERVER_SPEED*sin(theta_free)*cos(phi_free);
			posicao_observador.x+=OBSERVER_SPEED*cos(theta_free)*cos(phi_free);
			posicao_observador.y+=OBSERVER_SPEED*sin(phi_free);
		}break;
		case 's':{
			posicao_observador.z-=OBSERVER_SPEED*sin(theta_free)*cos(phi_free);
			posicao_observador.x-=OBSERVER_SPEED*cos(theta_free)*cos(phi_free);
			posicao_observador.y-=OBSERVER_SPEED*sin(phi_free);
		}break;
		case 'a':{
			posicao_observador.x+=OBSERVER_SPEED*sin(theta_free);
			posicao_observador.z-=OBSERVER_SPEED*cos(theta_free);
		}break;
		case 'd':{				
			posicao_observador.x-=OBSERVER_SPEED*sin(theta_free);
			posicao_observador.z+=OBSERVER_SPEED*cos(theta_free);
		}break;
		case 'i':{
			posicao_observador.z-=OBSERVER_SPEED*sin(theta_free)*sin(phi_free);
			posicao_observador.x-=OBSERVER_SPEED*cos(theta_free)*sin(phi_free);
			posicao_observador.y+=OBSERVER_SPEED*cos(phi_free);
		}break;
		case 'k':{
			posicao_observador.z+=OBSERVER_SPEED*sin(theta_free)*sin(phi_free);
			posicao_observador.x+=OBSERVER_SPEED*cos(theta_free)*sin(phi_free);
			posicao_observador.y-=OBSERVER_SPEED*cos(phi_free);
		}break;
		case '1': observer_change_mode(FREE_CAMERA);
		break;
		case '2': observer_change_mode(THIRD_UP);
		break;
		case '3': observer_change_mode(GEO_ESTACIONARIA);
		break;
	}
}
void keyboard_third_person(unsigned char key,int x, int y){
	switch(key){
		case '\t':{
			if(glutGetModifiers() == GLUT_ACTIVE_SHIFT){
				if(id_observado == Boid::idcont-1){
					id_observado = 0;
				} else {
					id_observado++;
				}
			} else {
				if(id_observado == 0){
					id_observado = Boid::idcont-1;
				} else {
					id_observado--;
				}
			}
			break;
		}
		case 'a': theta_geoestacionaria -= .01;
		break;
		case 'd': theta_geoestacionaria += .01;
		break;
		case 'w': distancia_geoestacionaria -=5;
		break;
		case 's': distancia_geoestacionaria +=5;
		break;
		case '1': observer_change_mode(FREE_CAMERA);
		break;
		case '2': observer_change_mode(THIRD_UP);
		break;
		case '3': observer_change_mode(GEO_ESTACIONARIA);
		break;
	}
}


int last_x=0, last_y=0;
void passive_mouse(int x, int y){
	last_x = x;
	last_y = y;
}
void active_mouse(int x, int y){
	
	int dx = x-last_x;
	int dy = y-last_y;
	last_x = x;
	last_y = y;	
	
	theta_free += (double)dx/1000.0;
	phi_free -= (double)dy/1000.0;
	if(phi_free > 89.0/180*PI)phi_free = 89.0/180*PI;
	else if(phi_free < -89.0/180*PI) phi_free = -89.0/180*PI;
	
}
void active_mouse_unused(int x,int y){}

void wheel_mouse(int button, int status, int x, int y){
	switch(button){
		case 3:{
			posicao_observador.z+=OBSERVER_SPEED*sin(theta_free)*cos(phi_free);
			posicao_observador.x+=OBSERVER_SPEED*cos(theta_free)*cos(phi_free);
			posicao_observador.y+=OBSERVER_SPEED*sin(phi_free);
		}break;
		case 4:{
			posicao_observador.z-=OBSERVER_SPEED*sin(theta_free)*cos(phi_free);
			posicao_observador.x-=OBSERVER_SPEED*cos(theta_free)*cos(phi_free);
			posicao_observador.y-=OBSERVER_SPEED*sin(phi_free);
		}break;
	}
}

void observer_change_mode(int mode){
	modo_observacao = mode;
	switch(modo_observacao){
		case FREE_CAMERA:{
			glutMotionFunc(active_mouse);
			glutMouseFunc(wheel_mouse);
			glutKeyboardFunc(keyboard_free_camera);
			break;
		}
		case THIRD_UP:{			
			glutMotionFunc(active_mouse_unused);
			glutMouseFunc(wheel_mouse);
			glutKeyboardFunc(keyboard_third_person);
			break;
		}
		case GEO_ESTACIONARIA:{
			glutMotionFunc(active_mouse_unused);
			glutMouseFunc(wheel_mouse);
			glutKeyboardFunc(keyboard_third_person);
			break;
		}
	}
}

void observer_init(Planeta *planet){
	glutPassiveMotionFunc(passive_mouse);
	observer_change_mode(FREE_CAMERA);
	planeta = planet;
	
}