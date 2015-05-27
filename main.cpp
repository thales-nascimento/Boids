#include <GL/freeglut.h>
#include <cmath>
#include <GL/glu.h>
#include "Boid_container.hpp"
#include "Planeta.hpp"
#include "observer.hpp"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH WINDOW_HEIGHT*2

double window_height = WINDOW_HEIGHT;
double window_width = WINDOW_WIDTH;

Planeta terra(INCLINACAO_TERRA, PERIODO_ROT_TERRA, PERIODO_TRANS_TERRA, GRAVIDADE_TERRA, RAIO_TERRA, DIST_TERRA_SOL);
Planeta sol(0,PERIODO_ROT_SOL,1,1,RAIO_SOL,0);
Planeta marte(INCLINACAO_MARTE, PERIODO_ROT_MARTE, PERIODO_TRANS_MARTE, GRAVIDADE_MARTE, RAIO_MARTE, DIST_MARTE_SOL);

Hud hud(WINDOW_WIDTH,WINDOW_HEIGHT);

void draw_scene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glViewport (0,0, window_width, window_height); 
	
	glPushMatrix();
		observer_look();
		
		glColor3ub(0xff,0xff,0);
		terra.draw();
		
		glColor3ub(0xff,0xff,0);
		marte.draw();
		
		glColor3ub(0xff,0xff,0);
		sol.draw();
		
		
	glPopMatrix();
	hud.draw();
	
	glutSwapBuffers();
}

void reshape (int w, int h){
	double ratio = (double)w/(double)h;
	window_height = h;
	window_width = w/ratio*2;
	glViewport (0,0, window_width, window_height); 
	hud.resize(w,h);
}

void boids_main_loop(int value){
	if(observer_pause){
		glutTimerFunc(TAXA_DE_ATUALIZACAO/2, boids_main_loop, value);
		return;
	}
	if(value){
		glutTimerFunc(TAXA_DE_ATUALIZACAO/2, boids_main_loop, !value);
		terra.refresh();
		marte.refresh();
		sol.refresh();
	}else{
		glutTimerFunc(TAXA_DE_ATUALIZACAO/2, boids_main_loop, !value);
		glutPostRedisplay();
	}

	
}

int main(int argc, char**argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutCreateWindow("boids");
	
	glutDisplayFunc(draw_scene);
	glutReshapeFunc(reshape);
	glutTimerFunc(60, boids_main_loop, 1);
	
	glEnable(GL_DEPTH_TEST);
	
	glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	glFrustum(-.25,.25,-.125,.125,1,DIST_TERRA_SOL  + RAIO_SOL);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
	
	observer_init(&terra, &hud);
	Boid::compile_vertexes();
	Planeta::compile_vertexes();
	terra.change_color(0x79,0x79,0xff);
	marte.change_color(0xff,0x79,0x79);
	sol.change_color(0xff,0xff,0x79);

	
	for(int i=0;i<1;i++){
		terra.boid_container.add_boid_rand();
	}
	terra.boid_container.designa_lider(0);
	
	glutMainLoop();
}

