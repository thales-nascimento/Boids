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

Planeta planetas[N_PLANETAS] = {
		Planeta(INCLINACAO_TERRA, PERIODO_ROT_TERRA, PERIODO_TRANS_TERRA, GRAVIDADE_TERRA, RAIO_TERRA, DIST_TERRA_SOL),
		Planeta(0,PERIODO_ROT_SOL,1,-1,RAIO_SOL,0),
		Planeta(INCLINACAO_MARTE, PERIODO_ROT_MARTE, PERIODO_TRANS_MARTE, GRAVIDADE_MARTE, RAIO_MARTE, DIST_MARTE_SOL)
		};
enum planets {terra=0,sol,marte};


Hud hud(WINDOW_WIDTH,WINDOW_HEIGHT);

void draw_scene(){
	
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glViewport (0,0, window_width, window_height); 
	
	glPushMatrix();
		observer_look();
		
		for(int i=0;i<N_PLANETAS;i++){
			glColor3ub(0xff,0xff,0);
			planetas[i].draw();
		}
		
		
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
		
		for(int i=0;i<N_PLANETAS;i++){
			planetas[i].refresh();
		}
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
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	const float luz_difuse[] = {1, .5f, .5f, 0};
	const float position[] = {0,.0,.0,0};
	const float mat_difuse[] = {0.5,0.5,0.5,0};
	const float luz_ambient[] = {0.1,0.1,0.2,0};
	const float ZERO[] = {.0,.0,.0,.0};
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ZERO);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ZERO);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuse);
	
	
	
	
	
	glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	glFrustum(-.25,.25,-.125,.125,1,DIST_TERRA_SOL  + RAIO_SOL);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
	
	observer_init(planetas, N_PLANETAS, &hud);
	Boid::compile_vertexes();
	Planeta::compile_vertexes();
	planetas[terra].change_color(0x79,0x79,0xff);
	planetas[marte].change_color(0xff,0x79,0x79);
	planetas[sol].change_color(0xff,0xff,0x79);

	
	for(int i=0;i<1;i++){
		planetas[terra].boid_container.add_boid_rand();
	}
	planetas[terra].boid_container.designa_lider(0);
	
	glutMainLoop();
}

