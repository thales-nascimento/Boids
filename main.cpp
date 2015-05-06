#include <GL/freeglut.h>
#include <cmath>
#include "Boid_container.hpp"
#include "Earth.h"

int move_speed = 4;
int pause = false;

double theta=0, phi=0;
												Boid lider(0,0,0);					///LIDER 
												Boid_container container(lider);	///CONTAINER GLOBAL
void draw_scene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
		glRotated(-theta, 1,0,0);
		glRotated(-phi,0,1,0);
		
		earth_draw();
		container.draw_boids();
	
	glPopMatrix();
	
	glutSwapBuffers();
}

void reshape (int w, int h){
	double ratio = (double)w/(double)h;
	glViewport (0,0, w/ratio*2, h); 
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
	
	theta += (double)dy/10.0;
	phi += (double)dx/10.0;
	glutPostRedisplay();
	
}
void wheel_mouse(int button, int status, int x, int y){
	switch(button){
		case 3:	glTranslatef(0,0,move_speed);
		break;
		case 4:	glTranslatef(0,0,-move_speed);
		break;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key,int x, int y){
	switch(key){
		case 'p': pause = !pause;
		break;
		case 'w': glTranslatef(0,-move_speed,0);
		break;
		case 's': glTranslatef(0,move_speed,0);
		break;
		case 'a': glTranslatef(move_speed,0,0);
		break;
		case 'd': glTranslatef(-move_speed,0,0);
		break;
		case '+':move_speed += move_speed>32?0:2;
		break;
		case '-':move_speed -= move_speed>0?0:2;
	}
	glutPostRedisplay();
}



void boids_main_loop(int value){
	if(pause){
		glutTimerFunc(15, boids_main_loop, value);
		return;
	}
	glutTimerFunc(15, boids_main_loop, !value);
	if(value){
		container.refresh_boids();
	} else {
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
	glFrustum(-32,32,-16,16,128,4096);
	glTranslatef(0,-16,-256);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
	
	Boid::compile_vertexes();
	earth_init();
	
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	container.add_boid(SPHERE_RADIUS+2,SPHERE_RADIUS+4);
	
	

	
	
	glutMainLoop();
	
	
}

