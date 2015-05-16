#include "Observer.hpp"

bool Observer::pause=false;
double Observer::theta=0, Observer::phi=0;
float Observer::distancia=RAIO_TERRESTRE+10;
int Observer::modo_observacao = FREE_CAMERA;
unsigned int id_observado=10;

void Observer::look(){
	switch(modo_observacao){
		case FREE_CAMERA:{
			double cosphi = cos(phi);
			double abscosphi = cosphi<0?-cosphi:cosphi;
			
			gluLookAt(posicao.x,posicao.y,posicao.z,
					posicao.x+abscosphi*cos(theta), posicao.y+sin(phi), posicao.z+abscosphi*sin(theta),
					cos(phi+PI/2)*cos(theta),cos(phi),cos(phi+PI/2)*sin(theta) );
			break;
		}
		case THIRD_UP:{			
			static unsigned int last_id=0;
			static Boid *observado;
			if(last_id != id_observado){
				last_id = id_observado;
				observado = earth->boid_container.procurar_boid(id_observado);
			}
			Vetor direcao = observado->get_coordenadas();
			Vetor v = direcao;
			posicao = direcao;
			direcao.normalizar();
			posicao += distancia*direcao;
			Vetor velocidade = observado->get_velocidade();
			double angulo_rotacao = earth->get_rotation();
			
			gluLookAt(posicao.x,posicao.y,posicao.z,  0,0,0,  velocidade.x, velocidade.y,velocidade.z );
		}	
	}
}

char move_left=0, move_right=0, move_front=0, move_back=0, move_top=0,move_bottom=0;
void Observer::move(){
	if(move_front){
		posicao.z+=OBSERVER_SPEED*sin(theta)*cos(phi);
		posicao.x+=OBSERVER_SPEED*cos(theta)*cos(phi);
		posicao.y+=OBSERVER_SPEED*sin(phi);
		move_front--;
	} else if(move_back){
		posicao.z-=OBSERVER_SPEED*sin(theta)*cos(phi);
		posicao.x-=OBSERVER_SPEED*cos(theta)*cos(phi);
		posicao.y-=OBSERVER_SPEED*sin(phi);
		move_back--;
	}
	if(move_left){
		posicao.x+=OBSERVER_SPEED*sin(theta);
		posicao.z-=OBSERVER_SPEED*cos(theta);
		move_left--;
	}else if(move_right){
		posicao.x-=OBSERVER_SPEED*sin(theta);
		posicao.z+=OBSERVER_SPEED*cos(theta);
		move_right--;
	}
	if(move_top){
		posicao.z-=OBSERVER_SPEED*sin(theta)*sin(phi);
		posicao.x-=OBSERVER_SPEED*cos(theta)*sin(phi);
		posicao.y+=OBSERVER_SPEED*cos(phi);
		move_top--;
	} else if(move_bottom){
		posicao.z+=OBSERVER_SPEED*sin(theta)*sin(phi);
		posicao.x+=OBSERVER_SPEED*cos(theta)*sin(phi);
		posicao.y-=OBSERVER_SPEED*cos(phi);
		move_bottom--;
	}
	
}

void keyboard_free_camera(unsigned char key,int x, int y){
	switch(key){
		case 'p': Observer::pause = !Observer::pause;
		break;
		case 'w': move_front = 3;
		break;
		case 's': move_back = 3;
		break;
		case 'a': move_left = 3;
		break;
		case 'd': move_right = 3;
		break;
		case 'i': move_top = 3;
		break;
		case 'k': move_bottom = 3;
		break;
		case '1': Observer::change_mode(FREE_CAMERA);
		break;
		case '2': Observer::change_mode(THIRD_UP);
		break;
	}
	glutPostRedisplay();
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
		case 'w': Observer::distancia +=2;
		break;
		case 'a': Observer::distancia -=2;
		break;
		case '1': Observer::change_mode(FREE_CAMERA);
		break;
		case '2': Observer::change_mode(THIRD_UP);
		break;
	}
	glutPostRedisplay();
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
	
	Observer::theta += (double)dx/1000.0;
	Observer::phi -= (double)dy/1000.0;
	if(Observer::phi > 89.0/180*PI)Observer::phi = 89.0/180*PI;
	else if(Observer::phi < -89.0/180*PI) Observer::phi = -89.0/180*PI;
	
	glutPostRedisplay();
	
}
void active_mouse_unused(int x,int y){}

void wheel_mouse(int button, int status, int x, int y){
	switch(button){
		case 3: move_front=5;
		break;
		case 4:	move_back=5;
		break;
	}
	glutPostRedisplay();
}

void Observer::change_mode(int mode){
	modo_observacao = mode;
	switch(modo_observacao){
		case FREE_CAMERA:{
			glutMotionFunc(active_mouse);
			glutPassiveMotionFunc(passive_mouse);
			glutMouseFunc(wheel_mouse);
			glutKeyboardFunc(keyboard_free_camera);
			break;
		}
		case THIRD_UP:{			
			glutMotionFunc(active_mouse_unused);
			glutPassiveMotionFunc(passive_mouse);
			glutMouseFunc(wheel_mouse);
			glutKeyboardFunc(keyboard_third_person);
			break;
		}
	}
}

void Observer::init(Earth *e){
	change_mode(FREE_CAMERA);
	earth = e;
	
}

Observer::Observer(){
}
