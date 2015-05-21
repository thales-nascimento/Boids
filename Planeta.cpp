#include "Planeta.hpp"



void Planeta::gravitacionar(){
	for(list<Boid>::iterator i = boid_container.boids.begin(); i != boid_container.boids.end(); i++){
		(*i).velocidade -= K_GRAVIDADE/(*i).coordenadas.norma()*(*i).coordenadas; 
	}
}


void Planeta::transladar(){
	const static double incremento = 1.0/TAXA_DE_ATUALIZACAO/PERIODO_TRANSLACAO;
	coordenadas.rotacionar_em_y(incremento);
}

void Planeta::refresh(){
	transladar();
	angulo_rotacao -= 1.0/TAXA_DE_ATUALIZACAO/PERIODO_ROTACAO;
	gravitacionar();
	boid_container.refresh_boids();
}

GLuint Planeta::esfera=0;
void Planeta::compile_vertexes(){
	esfera = glGenLists(1);
	
	glNewList(esfera, GL_COMPILE);
		glBegin(GL_QUADS);
			double phi=0, theta=0;
			for(int i=0;i<LATITUDES;i++){
				for(int j=0;j<LONGITUDES-1;j++){
					glVertex3d(cos(phi)*cos(theta), sin(phi) ,cos(phi)*sin(theta));
					theta += (PI*2/LATITUDES);
					glVertex3d(cos(phi)*cos(theta), sin(phi) ,cos(phi)*sin(theta));
					phi += (PI*2/LONGITUDES);
					glVertex3d(cos(phi)*cos(theta), sin(phi) ,cos(phi)*sin(theta));
					theta -= (PI*2/LATITUDES);				
					glVertex3d(cos(phi)*cos(theta), sin(phi) ,cos(phi)*sin(theta));
				}
				theta += (PI*2/LATITUDES);
			}
		glEnd();
	glEndList();
}

void Planeta::draw(){
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES );	
	
	glPushMatrix();
		glTranslated(coordenadas.x, coordenadas.y, coordenadas.z);
		draw_axis();
		glRotated(INCLINACAO_ROT*180.0/PI,1,0,0);
		glRotated(angulo_rotacao*180/PI, 0,1,0);
		boid_container.draw_boids();
		
		glScalef(RAIO,RAIO,RAIO);
		glColor3ub(0xff,0xff,0xff);
		glCallList(esfera);
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

double Planeta::get_rotation(){
	return angulo_rotacao;
}

Vetor Planeta::get_coordenadas(){
	return coordenadas;
}

Planeta::Planeta(double inclinacao_rotacao, unsigned int periodo_rotacao, unsigned int periodo_translacao, double constante_gravidade, unsigned int raio, double x,double y,double z):
	PERIODO_ROTACAO(periodo_rotacao),
	PERIODO_TRANSLACAO(periodo_translacao),
	INCLINACAO_ROT(inclinacao_rotacao),
	K_GRAVIDADE(constante_gravidade),
	RAIO(raio){
	angulo_rotacao = 0;
	boid_container.define_atmosfera(RAIO + ATMOSFERA_BOT, RAIO + ATMOSFERA_TOP);
	coordenadas.x = x;
	coordenadas.y = y;
	coordenadas.z = z;
}

