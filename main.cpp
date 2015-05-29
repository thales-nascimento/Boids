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
		Planeta(INCLINACAO_MARTE, PERIODO_ROT_MARTE, PERIODO_TRANS_MARTE, GRAVIDADE_MARTE, RAIO_MARTE, DIST_MARTE_SOL),
		
		Planeta(INCLINACAO_MERCURIO, PERIODO_ROT_MERCURIO, PERIODO_TRANS_MERCURIO, GRAVIDADE_MERCURIO, RAIO_MERCURIO, DIST_MERCURIO_SOL),
		Planeta(INCLINACAO_VENUS, PERIODO_ROT_VENUS, PERIODO_TRANS_VENUS, GRAVIDADE_VENUS, RAIO_VENUS, DIST_VENUS_SOL ),
		Planeta(INCLINACAO_JUPITER, PERIODO_ROT_JUPITER, PERIODO_TRANS_JUPITER, GRAVIDADE_JUPITER, RAIO_JUPITER, DIST_JUPITER_SOL),
		};
enum planets {terra=0,sol,marte,mercurio,venus,jupiter};


Hud hud(WINDOW_WIDTH,WINDOW_HEIGHT);

void draw_scene(){
		
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-.25,.25,-.125,.125,1,DIST_TERRA_SOL  + RAIO_SOL);		
		observer_look();
	glMatrixMode(GL_MODELVIEW);
	
	const float position[] = {.0,.0,.0,1};
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glDisable(GL_LIGHTING);
	planetas[0].draw();
	glEnable(GL_LIGHTING);
	for(int i=terra;i<N_PLANETAS;i++){
		planetas[i].draw();
	}
		
	hud.draw();
	
	glutSwapBuffers();
}


void boids_main_loop(int value){
	if(value || observer_pause){
		glutTimerFunc(TAXA_DE_ATUALIZACAO/2, boids_main_loop, !value);
		glutPostRedisplay();
	} else {
		glutTimerFunc(TAXA_DE_ATUALIZACAO/2, boids_main_loop, !value);
		
		for(int i=0;i<N_PLANETAS;i++){
			planetas[i].refresh();
		}
	}

	
}


int main(int argc, char**argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutCreateWindow("boids");
	
	glutDisplayFunc(draw_scene);
	//glutReshapeFunc(reshape);
	glutTimerFunc(60, boids_main_loop, 1);
	
	
	
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	const float luz_difuse[] = {.6, .6, .5, 0};
	const float mat_difuse[] = {1,1,1,0};
	const float ZERO[] = {.0,.0,.0,.0};
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difuse);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ZERO);        // Luz ambiente global
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuse);
	
	
	glMatrixMode(GL_PROJECTION);
	glFrustum(-.25,.25,-.125,.125,1,DIST_TERRA_SOL  + RAIO_SOL);
	glPushMatrix();
	glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	
	
	glPolygonMode(GL_FRONT, GL_FILL );
	
	observer_init(planetas, N_PLANETAS, &hud);
	Boid::compile_vertexes();
	planetas[terra].change_color(0x79,0x79,0xff);
	planetas[marte].change_color(0xff,0x79,0x79);
	planetas[sol].change_color(0xff,0xff,0x79);
	planetas[terra].change_color(0xff,0xff,0x79);

	
	for(int i=0;i<100;i++){
		planetas[terra].boid_container.add_boid_rand();
	}
	planetas[terra].boid_container.designa_lider(0);
	
	glutMainLoop();
}

