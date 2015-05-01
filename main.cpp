#include <GL/freeglut.h>
#include <cmath>
#include "Boid_container.hpp"
#include "consts.h"

int main(){
	Boid lider(0,0,0);
	Boid_container container(lider);
	container.add_boid(0,0,0);
	container.add_boid(1,32,0);
	container.add_boid(2,16,1);
	container.add_boid(4,8,2);
	container.add_boid(8,4,4);
	container.add_boid(12,2,8);
	container.add_boid(-12,1,16);
	container.add_boid(-8,-1,32);
	container.add_boid(-4,-2,0);
	container.add_boid(-2,-4,-2);
	container.add_boid(-1,-8,-16);
	
	
	list<Boid*> matches = container.esfera_visao(container[0]);
	for(list<Boid*>::iterator atual = matches.begin(); atual != matches.end(); atual++){
		cout<<(*atual)->get_coordenadas().x<<'	'<<(*atual)->get_coordenadas().y<<'	'<<(*atual)->get_coordenadas().z<<endl;
	}
	
	cout<<"_____________________\n";
	container.print_boids();
	

	
}

/*

void draw_scene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBegin(GL_QUADS);
	
		glColor3ub(63,191,63);
		glVertex3f(-50,-50,1);
		glVertex3f(-50,50,1);
		glVertex3f(50,50,1);
		glVertex3f(50,-50,1);
		
		glColor3ub(191,63,63);
		glVertex3f(-25,-25,0);
		glVertex3f(-25,25,0);
		glVertex3f(25,25,0);
		glVertex3f(25,-25,0);
		
		glColor3ub(63,63,191);
		glVertex3f(-75,-75,.4);
		glVertex3f(-75,75,.4);
		glVertex3f(75,75,.4);
		glVertex3f(75,-75,.4);
		
		
	glEnd();
	glutSwapBuffers();
}

void keyboard_func(unsigned char key, int x, int y){
	
}

void tick(int value){
	
	glutTimerFunc(30, tick, 0);
}

void reshape (int w, int h){
	double ratio = (double)w/(double)h;
   glViewport (0,0, w/ratio, h); 
   glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutCreateWindow("hi");
	
	glOrtho(-100,100,-100,100,-2,2);
	glutDisplayFunc(draw_scene);
	glutKeyboardFunc(keyboard_func);
	glutTimerFunc(30, tick, 0);
	glutReshapeFunc(reshape);
	
	glEnable(GL_DEPTH_TEST);
	
	glutMainLoop();
}*/

