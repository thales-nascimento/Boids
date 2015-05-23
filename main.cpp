#include <GL/freeglut.h>
#include <cmath>
#include <GL/glu.h>
#include "Boid_container.hpp"
#include "Planeta.hpp"
#include "observer.hpp"



Planeta terra(INCLINACAO_TERRA, PERIODO_ROT_TERRA, PERIODO_TRANS_TERRA, GRAVIDADE_TERRA, RAIO_TERRA, DIST_TERRA_SOL);
Planeta sol(0,PERIODO_ROT_SOL,1,1,RAIO_SOL,0);

void draw_scene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		observer_look();
		
		glColor3ub(0xff,0xff,0);
		terra.draw();
		
		glColor3ub(0xff,0xff,0);
		sol.draw();
		
		
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
		terra.refresh();
		sol.refresh();
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
	glFrustum(-.25,.25,-.125,.125,1,DIST_TERRA_SOL  + RAIO_SOL);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
	
	observer_init(&terra);
	Boid::compile_vertexes();
	Planeta::compile_vertexes();
	terra.change_color(0x79,0x79,0xff);
	sol.change_color(0xff,0xff,0x79);
	
	for(int i=0;i<200;i++){
		terra.boid_container.add_boid_rand();
	}
	terra.boid_container.designa_lider(0);
	
	glutMainLoop();
}

