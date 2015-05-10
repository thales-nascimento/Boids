#include <GL/freeglut.h>
#include <cmath>
#include <GL/glu.h>
#include "Boid_container.hpp"
#include "Earth.hpp"

#define OBSERVER_SPEED 8


int pause = false;


double theta=0, phi=0;
double observer_x=0,observer_y=0,observer_z=0;

Earth mundo;	
void draw_scene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	double cosphi = cos(phi);
	double abscosphi = cosphi<0?-cosphi:cosphi;
	glPushMatrix();
		gluLookAt(observer_x,observer_y,observer_z,observer_x+abscosphi*cos(theta), observer_y+sin(phi), observer_z+abscosphi*sin(theta),0,1,0);
		
		mundo.earth_draw();
		mundo.earth_debug();
		
		mundo.sun_draw();
		
	glPopMatrix();
	
	glutSwapBuffers();
}

void reshape (int w, int h){
	double ratio = (double)w/(double)h;
	glViewport (0,0, w/ratio*2, h); 
}





char move_left=0, move_right=0, move_front=0, move_back=0;
void keyboard(unsigned char key,int x, int y){
	switch(key){
		case 'p': pause = !pause;
		break;
		case 'w': move_front = 3;
		break;
		case 's': move_back = 3;
		break;
		case 'a': move_left = 3;
		break;
		case 'd': move_right = 3;
		break;
	}
	glutPostRedisplay();
}

void move_observer(){
	if(move_front){
		observer_z+=OBSERVER_SPEED*sin(theta);
		observer_x+=OBSERVER_SPEED*cos(theta);
		observer_y+=OBSERVER_SPEED*sin(phi);
		move_front--;
	} else if(move_back){
		observer_z-=OBSERVER_SPEED*sin(theta);
		observer_x-=OBSERVER_SPEED*cos(theta);
		observer_y-=OBSERVER_SPEED*sin(phi);
		move_back--;
	}
	if(move_left){
		observer_x+=OBSERVER_SPEED*sin(theta);
		observer_z-=OBSERVER_SPEED*cos(theta);
		move_left--;
	}else if(move_right){
		observer_x-=OBSERVER_SPEED*sin(theta);
		observer_z+=OBSERVER_SPEED*cos(theta);
		move_right--;
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
	
	theta += (double)dx/1000.0;
	phi -= (double)dy/1000.0;
	if(phi > 89.0/180*PI)phi = 89.0/180*PI;
	else if(phi < -89.0/180*PI) phi = -89.0/180*PI;
	
	glutPostRedisplay();
	
}
void wheel_mouse(int button, int status, int x, int y){
	switch(button){
		case 3: move_front=5;
		break;
		case 4:	move_back=5;
		break;
	}
	glutPostRedisplay();
}


void boids_main_loop(int value){
	if(pause){
		glutTimerFunc(15, boids_main_loop, value);
		return;
	}
	if(value){
		glutTimerFunc(15, boids_main_loop, !value);
		mundo.refresh();
		move_observer();
	}else{
		glutTimerFunc(15, boids_main_loop, !value);
		glutPostRedisplay();
	}

	
}

int main(int argc, char**argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1200,600);
	glutCreateWindow("boids");
	
	glutDisplayFunc(draw_scene);
	glutMotionFunc(active_mouse);
	glutPassiveMotionFunc(passive_mouse);
	glutMouseFunc(wheel_mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(60, boids_main_loop, 1);
	
	glEnable(GL_DEPTH_TEST);
	
	glViewport(0,0,1200,600);
	glFrustum(-32,32,-16,16,128,2048*RAIO_TERRESTRE);
	glTranslatef(0,-16,-256);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
	
	Boid::compile_vertexes();
	Earth::compile_vertexes();
	
	for(int i=0;i<100;i++){
		mundo.boid_container.add_boid(RAIO_TERRESTRE+1,RAIO_TERRESTRE+8);
	}
	
	glutMainLoop();
	
	
}

