#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
using namespace std;

#define PI 3.14159265

GLuint cube;
void compile_cube(){
	cube = glGenLists(1);
	
	glNewList(cube, GL_COMPILE);
		glBegin(GL_QUADS);
			
			glColor3ub(0xff,0xff,0xff);
			
			glVertex3d(1,1,1);		//top
			glVertex3d(1,-1,1);
			glVertex3d(-1,-1,1);
			glVertex3d(-1,1,1);
			
			glVertex3d(1,1,1);		//north
			glVertex3d(-1,1,1);
			glVertex3d(-1,1,-1);
			glVertex3d(1,1,-1);
			
			glVertex3d(1,1,1);		//east
			glVertex3d(1,1,-1);
			glVertex3d(1,-1,-1);
			glVertex3d(1,-1,1);
			
			glVertex3d(-1,-1,-1);	//bottom
			glVertex3d(1,-1,-1);
			glVertex3d(1,1,-1);
			glVertex3d(-1,1,-1);
			
			glVertex3d(-1,-1,-1);	//east
			glVertex3d(-1,1,-1);
			glVertex3d(-1,1,1);
			glVertex3d(-1,-1,1);
			
			glVertex3d(-1,-1,-1);	//south
			glVertex3d(-1,-1,1);
			glVertex3d(1,-1,1);
			glVertex3d(1,-1,-1);
		glEnd();
	glEndList();
}
void draw_cube(){
	glCallList(cube);
}

void draw_scene(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glTranslatef(0,0,-8);
	draw_cube();
	glTranslatef(-2,0,2);
	glScalef(.5,.5,.5);
	draw_cube();
	glScalef(2,2,2);
	glTranslatef(2,0,6);
	glutSwapBuffers();
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
	
	glRotated((double)dx/10.0,0,1,0);
	glRotated((double)dy/10.0,1,0,0);
	glutPostRedisplay();
	
}

void keyboard(unsigned char key,int x, int y){

	switch(key){
		case 'w': glTranslatef(0,0,-.25);
		break;
		case 's': glTranslatef(0,0,.25);
		break;
		case 'a': glTranslatef(.25,0,0);
		break;
		case 'd': glTranslatef(-.25,0,0);
		break;
		case 'u': glTranslatef(0,.25,0);
		break;
		case 'j': glTranslatef(0,-.25,0);
	}
	glutPostRedisplay();
}

void reshape (int w, int h){
	double ratio = (double)w/(double)h;
	glViewport (0,0, w/ratio, h); 
}

int main(int argc, char** argv){
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutCreateWindow("cube ortho");
	
	glFrustum(-4,4,-4,4,4,12);
	
	glPushMatrix();
	
	glutDisplayFunc(draw_scene);
	glutMotionFunc(active_mouse);
	glutPassiveMotionFunc(passive_mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
	compile_cube();
	
	glutMainLoop();
}

