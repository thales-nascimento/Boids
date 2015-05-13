#include <GL/freeglut.h>
#include <cmath>
#include <GL/glu.h>
#include "Boid_container.hpp"
#include "Earth.hpp"
#include "Observer.hpp"

Earth mundo;
Observer observer;

void draw_scene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		observer.look();
		
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






void boids_main_loop(int value){
	observer.move();
	if(observer.pause){
		glutTimerFunc(15, boids_main_loop, value);
		return;
	}
	if(value){
		glutTimerFunc(15, boids_main_loop, !value);
		mundo.refresh();
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
	glutReshapeFunc(reshape);
	glutTimerFunc(60, boids_main_loop, 1);
	
	glEnable(GL_DEPTH_TEST);
	
	glViewport(0,0,1200,600);
	glFrustum(-2,2,-1,1,8,2048*RAIO_TERRESTRE);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
	
	observer.init(&mundo);
	Boid::compile_vertexes();
	Earth::compile_vertexes();
	
	for(int i=0;i<200;i++){
		mundo.boid_container.add_boid(RAIO_TERRESTRE+1,RAIO_TERRESTRE+8);
	}
	
	glutMainLoop();
}

