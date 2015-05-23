#include "observer.hpp"

#define FREE_CAMERA 0
#define THIRD_UP 1
#define THIRD_SIDE 2
#define GEO_ESTACIONARIA 3
#define FIRST 4
#define OBSERVER_SPEED 8

Planeta *planeta;

bool observer_pause=false;
int modo_observacao = FREE_CAMERA;

unsigned int id_observado=0;

double theta_geoestacionaria = 0;
double theta_free=0, phi_free=0;
float distancia_terceira_pessoa=RAIO_TERRA+1000;

Vetor posicao_observador;

void observer_look(){
	switch(modo_observacao){
		case FREE_CAMERA:{
			double cosphi = cos(phi_free);
			double abscosphi = cosphi<0?-cosphi:cosphi;
			
			gluLookAt(posicao_observador.x,posicao_observador.y,posicao_observador.z,
					posicao_observador.x+abscosphi*cos(theta_free), posicao_observador.y+sin(phi_free), posicao_observador.z+abscosphi*sin(theta_free),
					cos(phi_free+PI/2)*cos(theta_free),cos(phi_free),cos(phi_free+PI/2)*sin(theta_free) );
		}break;
		case FIRST:
		case THIRD_SIDE:
		case THIRD_UP:{			
			static unsigned int last_id=0;
			static Boid* last_boid = planeta->boid_container.procurar_boid(last_id);
			if(last_id != id_observado){
				last_id = id_observado;
				last_boid = planeta->boid_container.procurar_boid(last_id);
			}
			Vetor centro = planeta->get_coordenadas();
			Vetor up;
			
			Vetor posicao_observador = last_boid->get_coordenadas();
			posicao_observador.rotacionar_em_y(-planeta->get_rotation());
			posicao_observador.rotacionar_em_x(planeta->INCLINACAO_ROT);
			
			if(modo_observacao == THIRD_SIDE){
				posicao_observador.normalizar();	
				posicao_observador += produto_vetorial(posicao_observador, Vetor(0,cos(planeta->INCLINACAO_ROT),sin(planeta->INCLINACAO_ROT)));
				up = last_boid->get_coordenadas();
				up.rotacionar_em_y(-planeta->get_rotation());
				up.rotacionar_em_x(planeta->INCLINACAO_ROT);
				posicao_observador *= distancia_terceira_pessoa;
				posicao_observador += centro;
				centro += up;
			
			} else if(modo_observacao == THIRD_UP){ 
				posicao_observador.normalizar();
				up = produto_vetorial(posicao_observador, Vetor(0,cos(planeta->INCLINACAO_ROT),sin(planeta->INCLINACAO_ROT)));
				posicao_observador *= distancia_terceira_pessoa;
				posicao_observador += centro;
			
			} else {
				up = posicao_observador;
				Vetor velocidade = last_boid->get_velocidade();
				velocidade.rotacionar_em_y(-planeta->get_rotation());
				velocidade.rotacionar_em_x(planeta->INCLINACAO_ROT);
				centro += posicao_observador + velocidade;
				posicao_observador = centro - velocidade;
			}
			
			gluLookAt(posicao_observador.x,posicao_observador.y,posicao_observador.z,
					centro.x,centro.y,centro.z,
					up.x,up.y,up.z);
			
					
		}break;
		case GEO_ESTACIONARIA:{
			double rotacao = planeta->get_rotation();
			Vetor posicao_observador(distancia_terceira_pessoa,0,0);
			posicao_observador.rotacionar_em_y(-rotacao + theta_geoestacionaria);
			posicao_observador.rotacionar_em_x(planeta->INCLINACAO_ROT);
			
			Vetor centro = planeta->get_coordenadas();
			posicao_observador += centro;
			
			gluLookAt(posicao_observador.x,posicao_observador.y,posicao_observador.z,
					centro.x,centro.y,centro.z,
					0,cos(planeta->INCLINACAO_ROT),sin(planeta->INCLINACAO_ROT));
		}break;
	}
	
	glutPostRedisplay();
}

void change_camera(unsigned char key){
	switch(key){
		case '1': observer_change_mode(FREE_CAMERA);
		break;
		case '2': observer_change_mode(THIRD_UP);
		break;
		case '3': observer_change_mode(THIRD_SIDE);
		break;
		case '4': observer_change_mode(GEO_ESTACIONARIA);
		break;
		case '5': observer_change_mode(FIRST);
		break;
	}
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
		default:change_camera(key);
	}
}
void keyboard_third(unsigned char key,int x, int y){
	switch(key){
		case 'p': observer_pause = !observer_pause;
		break;
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
		case 'w': distancia_terceira_pessoa -=5;
		break;
		case 's': distancia_terceira_pessoa +=5;
		break;
		default:change_camera(key);
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

void wheel_mouse_free(int button, int status, int x, int y){
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
void wheel_mouse_third(int button, int status, int x, int y){
	switch(button){
		case 3:{
			distancia_terceira_pessoa -= 10;
		}break;
		case 4:{
			distancia_terceira_pessoa += 10;
		}break;
	}
}

void observer_change_mode(int mode){
	modo_observacao = mode;
	switch(modo_observacao){
		case FREE_CAMERA:{
			glutMotionFunc(active_mouse);
			glutMouseFunc(wheel_mouse_free);
			glutKeyboardFunc(keyboard_free_camera);
		}break;
		case FIRST:
		case THIRD_UP:
		case THIRD_SIDE:{
			glutMotionFunc(active_mouse_unused);
			glutMouseFunc(wheel_mouse_third);
			glutKeyboardFunc(keyboard_third);
		}break;
		case GEO_ESTACIONARIA:{
			glutMotionFunc(active_mouse_unused);
			glutMouseFunc(wheel_mouse_third);
			glutKeyboardFunc(keyboard_third);
		}break;
	}
}

void observer_init(Planeta *planet){
	glutPassiveMotionFunc(passive_mouse);
	observer_change_mode(FREE_CAMERA);
	posicao_observador = planet->get_coordenadas();
	posicao_observador.z -=  planet->RAIO*2;
	theta_free += PI/2;
	planeta = planet;
	
}
