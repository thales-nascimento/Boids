#include "observer.hpp"

#define N_CAMERAS 5
#define FREE_CAMERA 1
#define THIRD_UP 2
#define THIRD_SIDE 3
#define GEO_ESTACIONARIA 4
#define FIRST 5
#define OBSERVER_SPEED 8

int n_planetas;
int planeta_atual = 1;
Planeta *planeta;

int id_observado=-1;
Boid* last_boid;
int lider_atual = -1;

Hud *_hud;
unsigned int string_camera, string_n_boids, string_boid_observado, string_coordenadas, string_planeta, string_lider;	//identificadores para mudar as strings do hud
const char* NOMES_PLANETAS[N_PLANETAS] = {"Terra", "Sol", "Marte", "Mercurio", "Venus", "Jupiter"};


bool observer_pause=false;
int modo_observacao = FREE_CAMERA;

double theta_geoestacionaria = 0;
double theta_free=0, phi_free=0;
float distancia_terceira_pessoa=RAIO_TERRA+1000;
Vetor posicao_observador;


void observer_change_mode(int mode);

//callbacks para o teclado
//_---_-___--__-_-_--___--_--_--___--____-_--__-___--_----
void keyboard_generico(unsigned char key){
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
		case 13: planeta->boid_container.toggle_setpoint();		//ENTER
		break;
		case '+': planeta->boid_container.add_boid_rand();
		break;
		case 'D': Boid::model = !Boid::model;
		break;
		case 'l':{
			static float luz_ambient[] = {0,0,0,0};
			static bool comutador = true;
			if(comutador){
				luz_ambient[0] = luz_ambient[1] = .2;
				luz_ambient[2] = .15;
			} else {
				luz_ambient[0] = luz_ambient[1] = luz_ambient[2] = 0;
			}
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambient);
			comutador = !comutador;
			
		}break;
		case '-':{
			planeta->boid_container.remove_boid_rand();
			if(id_observado >= planeta->boid_container.get_n_boids()){
				id_observado--;
				if(id_observado < 0){
					modo_observacao = GEO_ESTACIONARIA;
					id_observado = -1;
				}
				observer_change_mode(modo_observacao);
			}
		}break;
		case '\t':{
			if(glutGetModifiers() == GLUT_ACTIVE_SHIFT){			
				if(id_observado >= planeta->boid_container.get_n_boids()-1){
					id_observado = 0;
				} else {
					id_observado++;
				}
			} else {
				if(id_observado <= 0){
					id_observado = planeta->boid_container.get_n_boids()-1;
				} else {
					id_observado--;
				}
			}
			observer_change_mode(modo_observacao);
		}break;
	}
}

void keyboard_setpoint(int key, int x, int y){
	static double phi=0,theta=0;
	switch(key){
		case GLUT_KEY_UP:phi+=.1;
		break;
		case GLUT_KEY_DOWN:phi-=.1;
		break;
		case GLUT_KEY_LEFT:theta -= .1;
		break;
		case GLUT_KEY_RIGHT:theta += .1;
		break;
	}
	
	planeta->boid_container.set_point(theta,phi);
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
		case 'r':{
			posicao_observador.z-=OBSERVER_SPEED*sin(theta_free)*sin(phi_free);
			posicao_observador.x-=OBSERVER_SPEED*cos(theta_free)*sin(phi_free);
			posicao_observador.y+=OBSERVER_SPEED*cos(phi_free);
		}break;
		case 'f':{
			posicao_observador.z+=OBSERVER_SPEED*sin(theta_free)*sin(phi_free);
			posicao_observador.x+=OBSERVER_SPEED*cos(theta_free)*sin(phi_free);
			posicao_observador.y-=OBSERVER_SPEED*cos(phi_free);
		}break;
		default:keyboard_generico(key);
	}
}
void keyboard_third(unsigned char key,int x, int y){
	switch(key){
		case 'p': observer_pause = !observer_pause;
		break;
		case 'a': theta_geoestacionaria -= .01;
		break;
		case 'd': theta_geoestacionaria += .01;
		break;
		case 'w': distancia_terceira_pessoa -=5;
		break;
		case 's': distancia_terceira_pessoa +=5;
		break;
		default:keyboard_generico(key);
	}
}



//callbacks para o mouse
//_--_--_-_--_----_---_-_-_---__--_--__-_-
int last_x=0, last_y=0;
void passive_mouse(int x, int y){
	last_x = x;
	last_y = y;
	
	_hud->hover_buttons(x,y,false);
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


void hud_mouse(int x,int y){	
	int acao = _hud->hover_buttons(x,y,true);
	switch(acao){
		case PROXIMO_BOID:{ 
			if(id_observado >= planeta->boid_container.get_n_boids()-1){
				id_observado = 0;
			} else {
				id_observado++;
			}
		}break;
		case BOID_ANTERIOR:{
			if(id_observado <= 0){
				id_observado = planeta->boid_container.get_n_boids()-1;
			} else {
				id_observado--;
			}
			observer_change_mode(modo_observacao);
		}break;
		case INCREMENTA_BOIDS: planeta->boid_container.add_boid_rand();
		break;
		case DECREMENTA_BOIDS: planeta->boid_container.remove_boid_rand();
		break;
		case PROXIMA_CAMERA:
		case CAMERA_ANTERIOR:{
			int ultima_camera = modo_observacao;
			if(acao == PROXIMA_CAMERA){
				if(ultima_camera == N_CAMERAS){
					ultima_camera = 1;
				} else ultima_camera++;
			} else {
				if(ultima_camera == 1){
					ultima_camera = N_CAMERAS;
				} else ultima_camera--;
			}
			observer_change_mode(ultima_camera);
		}
		break;
		case PROXIMO_PLANETA:
		case PLANETA_ANTERIOR:{
			if(acao == PROXIMO_PLANETA){
				if(planeta_atual == n_planetas){
					planeta_atual = 1;
					planeta -= (n_planetas-1);
				} else {
					planeta++;
					planeta_atual++;
				}
			} else {
				if(planeta_atual == 1){
					planeta_atual = n_planetas;
					planeta += (n_planetas-1);
				} else {
					planeta--;
					planeta_atual--;
				}
			}
			_hud->set_string(string_planeta, (char*)NOMES_PLANETAS[planeta_atual-1]);
			observer_change_mode(GEO_ESTACIONARIA);
			id_observado = -1;
			lider_atual = -1;
			last_boid = NULL;
		}break;
		case PROXIMO_LIDER:{
			if(lider_atual >= (int)planeta->boid_container.get_n_boids()){
				lider_atual = -1;
			} else {
				lider_atual++;
			}
			planeta->boid_container.designa_lider(lider_atual);
		}break;
		case LIDER_ANTERIOR:{
			if(lider_atual == -1){
				lider_atual = planeta->boid_container.get_n_boids()-1;
			} else {
				lider_atual--;
			}
			planeta->boid_container.designa_lider(lider_atual);
		}break;
	}
}

void mouse_free(int button, int status, int x, int y){
	switch(button){
		case 3:{		//rodinha do mouse
			posicao_observador.z+=OBSERVER_SPEED*sin(theta_free)*cos(phi_free);
			posicao_observador.x+=OBSERVER_SPEED*cos(theta_free)*cos(phi_free);
			posicao_observador.y+=OBSERVER_SPEED*sin(phi_free);
		}break;
		case 4:{		//rodinha do mouse
			posicao_observador.z-=OBSERVER_SPEED*sin(theta_free)*cos(phi_free);
			posicao_observador.x-=OBSERVER_SPEED*cos(theta_free)*cos(phi_free);
			posicao_observador.y-=OBSERVER_SPEED*sin(phi_free);
		}break;
		default:
			if(status == GLUT_UP)hud_mouse(x,y);
	}
}

void mouse_third(int button, int status, int x, int y){
	switch(button){
		case 3:{
			distancia_terceira_pessoa -= 10;
		}break;
		case 4:{
			distancia_terceira_pessoa += 10;
		}break;
		default:
			if(status == GLUT_UP)hud_mouse(x,y);
	}
}


//interface
//_--_-__-_--_---__---_-___--__-_-_---__-__--__--__--____-_--___--_--__-_-
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

			Vetor centro = planeta->get_coordenadas();
			Vetor up;
			
			posicao_observador = last_boid->get_coordenadas();
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
			posicao_observador = Vetor(distancia_terceira_pessoa + planeta->RAIO,0,0);
			posicao_observador.rotacionar_em_y(-rotacao + theta_geoestacionaria);
			posicao_observador.rotacionar_em_x(planeta->INCLINACAO_ROT);
			
			Vetor centro = planeta->get_coordenadas();
			posicao_observador += centro;
			
			gluLookAt(posicao_observador.x,posicao_observador.y,posicao_observador.z,
					centro.x,centro.y,centro.z,
					0,cos(planeta->INCLINACAO_ROT),sin(planeta->INCLINACAO_ROT));
		}break;
	}
	
		
	//setando as strings do HUD
	//os numeros são a quantidade de caracteres necessários definidos empiricamente
	static char aux_xyz[3][12], aux_observado[21], aux_lider[17], aux_n_boids[11];
	memset(aux_observado,0,21);
	memset(aux_lider,0,17);
	memset(aux_xyz,0,36);
	memset(aux_n_boids,0,11);
	
	sprintf(aux_n_boids, "%d Boids", planeta->boid_container.get_n_boids());
	sprintf(aux_observado, "boid observado: %d", id_observado);
	sprintf(aux_lider, "Lider: %d", lider_atual);
	sprintf(aux_xyz[2],"X: %i",(int)posicao_observador.x);	
	sprintf(aux_xyz[1],"Y: %i",(int)posicao_observador.y);
	sprintf(aux_xyz[0],"Z: %i",(int)posicao_observador.z);
	
	_hud->set_string(string_n_boids, aux_n_boids);
	_hud->set_string(string_lider, aux_lider);
	_hud->set_string(string_boid_observado, aux_observado);
	_hud->set_string(string_coordenadas, aux_xyz[0]);
	_hud->set_string(string_coordenadas+1, aux_xyz[1]);
	_hud->set_string(string_coordenadas+2, aux_xyz[2]);
}


//mudanca de cameras
//_________________________________________
void observer_change_mode(int mode){
	switch(mode){
		case FREE_CAMERA:{
			glutMotionFunc(active_mouse);
			glutMouseFunc(mouse_free);
			glutKeyboardFunc(keyboard_free_camera);
			_hud->set_string(string_camera,(char*)"camera livre");
		}break;
		case FIRST:
		case THIRD_UP:
		case THIRD_SIDE:{
			last_boid = (*planeta).boid_container[id_observado];
			if(last_boid == NULL){
				return;
			}
			
			switch(mode){
				case FIRST: _hud->set_string(string_camera, (char*)"primeira pessoa");
				break;
				case THIRD_UP: _hud->set_string(string_camera, (char*)"terceira pessoa (topo)");
				break;
				case THIRD_SIDE: _hud->set_string(string_camera, (char*)"terceira pessoa (lateral)");
				break;
			}
			glutMotionFunc(active_mouse_unused);
			glutMouseFunc(mouse_third);
			glutKeyboardFunc(keyboard_third);
		}break;
		case GEO_ESTACIONARIA:{
			glutMotionFunc(active_mouse_unused);
			glutMouseFunc(mouse_third);
			glutKeyboardFunc(keyboard_third);
			_hud->set_string(string_camera, (char*)"geoestacionária");
		}break;
	}
	modo_observacao = mode;
}

//inicializacao e criacao do HUD
void observer_init(Planeta *planet, int n_planets, Hud *h){
	n_planetas = n_planets;
	planeta = planet;
	
	_hud = h;	
	string_boid_observado = _hud->add_string(4,2,(char*)"boid observado: ");
	string_camera = _hud->add_string(4,5,(char*)"camera: ");
	string_n_boids = _hud->add_string(4,8,(char*)"N Boids");
	string_planeta = _hud->add_string(4,11,(char*)NOMES_PLANETAS[0]);
	string_lider = _hud->add_string(4,14,(char*)"Lider: ");
	
	string_coordenadas = _hud->add_string(1,17,(char*)"Z: ");
	_hud->add_string(1,20,(char*)"Y: ");
	_hud->add_string(1,23,(char*)"X: ");
	
	static char* larrow = (char*)"<";
	static char* rarrow = (char*)">";
	_hud->add_button(1,2,BOID_ANTERIOR,larrow);		_hud->add_button(2,2,PROXIMO_BOID,rarrow);
	_hud->add_button(1,5,CAMERA_ANTERIOR,larrow);	_hud->add_button(2,5,PROXIMA_CAMERA,rarrow);
	_hud->add_button(1,8,DECREMENTA_BOIDS,larrow);	_hud->add_button(2,8,INCREMENTA_BOIDS,rarrow);
	_hud->add_button(1,11,PLANETA_ANTERIOR,larrow);	_hud->add_button(2,11,PROXIMO_PLANETA,rarrow);
	_hud->add_button(1,14,LIDER_ANTERIOR,larrow);	_hud->add_button(2,14,PROXIMO_LIDER,rarrow);
	
	
	glutPassiveMotionFunc(passive_mouse);
	glutSpecialFunc(keyboard_setpoint);
	observer_change_mode(FREE_CAMERA);
	posicao_observador = planet->get_coordenadas();
	posicao_observador.z -=  planet->RAIO*2;
	theta_free += PI/2;
	

}
