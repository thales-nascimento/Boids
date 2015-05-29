#include "Planeta.hpp"



void Planeta::gravitacionar(){
	for(list<Boid>::iterator i = boid_container.boids.begin(); i != boid_container.boids.end(); i++){
		(*i).velocidade -= K_GRAVIDADE/(*i).coordenadas.norma()*(*i).coordenadas; 
	}
}


void Planeta::transladar(){
	const static double incremento = 1.0/(double)TAXA_DE_ATUALIZACAO/(double)PERIODO_TRANSLACAO;
	coordenadas.rotacionar_em_y(incremento);
}

void Planeta::refresh(){
	transladar();
	angulo_rotacao -= 1.0/TAXA_DE_ATUALIZACAO/PERIODO_ROTACAO;
	gravitacionar();
	boid_container.refresh_boids();
}


void Planeta::draw(){
	
	
	glPushMatrix();
		glTranslated(coordenadas.x, coordenadas.y, coordenadas.z);
		draw_axis();
		glRotated(INCLINACAO_ROT*180.0/PI,1,0,0);
		glRotated(angulo_rotacao*180/PI, 0,1,0);
		boid_container.draw_boids();
		
		glColor3ubv(color);
		glRotated(-90,1,0,0);
		glutSolidSphere(RAIO,20,20);
		
	glPopMatrix();
}

void Planeta::draw_axis(){
	glBegin(GL_LINES);
		glColor3ub(0xff,0,0);
		glVertex3i(RAIO*2048,0,0);
		glVertex3i(-RAIO*2048,0,0);
		glColor3ub(0,0,0xff);
		glVertex3i(0,RAIO*2048,0);
		glVertex3i(0,-RAIO*2048,0);
		glColor3ub(0,0xff,0);
		glVertex3i(0,0,RAIO*2048);
		glVertex3i(0,0,-RAIO*2048);
	glEnd();
}

void Planeta::change_color(unsigned char r, unsigned char g, unsigned char b){
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

double Planeta::get_rotation(){
	return angulo_rotacao;
}

Vetor Planeta::get_coordenadas(){
	return coordenadas;
}

Planeta::Planeta(double inclinacao_rotacao, float periodo_rotacao, float periodo_translacao, double constante_gravidade, unsigned int raio, int distancia_centro):
	PERIODO_ROTACAO(periodo_rotacao),
	PERIODO_TRANSLACAO(periodo_translacao),
	INCLINACAO_ROT(inclinacao_rotacao),
	K_GRAVIDADE(constante_gravidade),
	RAIO(raio){
	angulo_rotacao = 0;
	boid_container.define_atmosfera(RAIO + ATMOSFERA_BOT, RAIO + ATMOSFERA_TOP);
	int dist_x = 0;
	if(distancia_centro != 0)dist_x = rand() % distancia_centro;
	coordenadas.x = dist_x;
	coordenadas.z = distancia_centro - dist_x;
	color[0]=color[1]=color[2]=0xff;
}

