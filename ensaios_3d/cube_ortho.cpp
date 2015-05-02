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
	
	draw_cube();
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
	
	static double theta=PI/4, phi=PI/4;
	theta += (double)dx/10;
	phi += (double)dy/10;
	
	
	glPopMatrix();
	glPushMatrix();
	glRotated(theta,0,1,0);
	glRotated(phi,1,0,0);
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
	
	
	glOrtho(-10,10,-10,10,-10,10);
	
	glPushMatrix();
	
	glutDisplayFunc(draw_scene);
	glutMotionFunc(active_mouse);
	glutPassiveMotionFunc(passive_mouse);
	glutReshapeFunc(reshape);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
	compile_cube();
	
	glutMainLoop();
}
