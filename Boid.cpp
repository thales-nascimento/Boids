#include "Boid.hpp"

Boid::Boid(double x, double y, double z){
	coordenadas[0] = x;
	coordenadas[1] = y;
	coordenadas[2] = z;
	Vetor a(rand(),rand(),rand());
	mudar_aceleracao(a);
}

Boid::Boid(Vetor posicao){
	coordenadas = posicao;
}


Boid::Boid(){}


void Boid::acelerar(){
	velocidade += aceleracao;
	if(velocidade.norma() > VELOCIDADE_MAX){
		velocidade.normalizar();
		velocidade *= VELOCIDADE_MAX;
	}
}
void Boid::mover(){
	coordenadas += velocidade;
}


void Boid::refresh(){
	acelerar();
	mover();
}
void Boid::mudar_aceleracao(Vetor a){
	if(a.norma() > ACELERACAO_MAX){
		a.normalizar();
		a *= ACELERACAO_MAX;
	}
	aceleracao = a;
}

Vetor Boid::get_coordenadas(){
	return coordenadas;
}
Vetor Boid::get_velocidade(){
	return velocidade;
}
Vetor Boid::get_aceleracao(){
	return aceleracao;
}


GLuint Boid::boid = 0;
void Boid::compile_vertexes(){
	Boid::boid = glGenLists(1);
	glNewList(boid, GL_COMPILE);
		glColor3ub(0x79,0xff,0x79);
		glBegin(GL_TRIANGLES);
			glVertex3f(SCALER*cos(PI*2/3),SCALER*sin(PI*2/3),-SCALER);
			glVertex3f(SCALER*cos(PI*4/3),SCALER*sin(PI*4/3),-SCALER);
			glVertex3f(SCALER*cos(PI*2),SCALER*sin(PI*2),-SCALER);
			
			glVertex3f(SCALER*cos(PI*2/3),SCALER*sin(PI*2/3),-SCALER);
			glVertex3f(SCALER*cos(PI*4/3),SCALER*sin(PI*4/3),-SCALER);
			glVertex3f(0,0,2*SCALER);
			
			glVertex3f(SCALER*cos(PI*4/3),SCALER*sin(PI*4/3),-SCALER);
			glVertex3f(SCALER*cos(PI*2),SCALER*sin(PI*2),-SCALER);
			glVertex3f(0,0,2*SCALER);
			
			glVertex3f(SCALER*cos(PI*2),SCALER*sin(PI*2),-SCALER);
			glVertex3f(SCALER*cos(PI*2/3),SCALER*sin(PI*2/3),-SCALER);
			glVertex3f(0,0,2*SCALER);
		
		glEnd();
	glEndList();
}

void Boid::draw(){
	double rotx,roty,rotz;
	if(velocidade.norma() != 0){
		rotx = acos(produto_escalar(velocidade, {1,0,0})/velocidade.norma());
		roty = acos(produto_escalar(velocidade, {0,1,0})/velocidade.norma());
		rotz = acos(produto_escalar(velocidade, {0,0,1})/velocidade.norma());
	
	} else {
		rotx = rotz = roty = 0;
	}
	
	glRotated(rotx,1,0,0); 
	glRotated(roty,0,1,0); 
	glRotated(rotz,0,0,1); 
	glCallList(Boid::boid);
}
