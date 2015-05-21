#include <GL/freeglut.h>
#include <cmath>
#include <GL/glu.h>
#include "Boid_container.hpp"
#include "Planeta.hpp"
#include "observer.hpp"



Planeta mundo(INCLINACAO_TERRA, PERIODO_ROT_TERRA, PERIODO_TRANS_TERRA, GRAVIDADE_TERRA, RAIO_TERRA, 100,0,0);

void draw_scene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		observer_look();
		
		mundo.draw();
		
		
	glPopMatrix();
	
	glutSwapBuffers();
}

void reshape (int w, int h){
	double ratio = (double)w/(double)h;
	glViewport (0,0, w/ratio*2, h); 
}

void boids_main_loop(int value){
	if(observer_pause){
		glutTimerFunc(TAXA_DE_ATUALIZACAO/2, boids_main_loop, value);
		return;
	}
	if(value){
		glutTimerFunc(TAXA_DE_ATUALIZACAO/2, boids_main_loop, !value);
		mundo.refresh();
	}else{
		glutTimerFunc(TAXA_DE_ATUALIZACAO/2, boids_main_loop, !value);
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
	glFrustum(-2,2,-1,1,8,2048*RAIO_TERRA);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
	
	observer_init(&mundo);
	Boid::compile_vertexes();
	Planeta::compile_vertexes();
	
	for(int i=0;i<200;i++){
		mundo.boid_container.add_boid_rand();
	}
	mundo.boid_container.designa_lider(0);
	
	glutMainLoop();
}

