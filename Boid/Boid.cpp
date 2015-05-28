#include "Boid.hpp"

double Boid::VELOCIDADE_MAX = .1;
double Boid::ACELERACAO_MAX = .005;
double Boid::CAMPO_DE_VISAO = 6;
unsigned int Boid::idcont=0;


Boid::Boid(double x, double y, double z): id(idcont){
	coordenadas[0] = x;
	coordenadas[1] = y;
	coordenadas[2] = z;
	Vetor a(rand(),rand(),rand());
	mudar_aceleracao(a);
	
	vizinhos_vistos=0;
	
}

Boid::Boid(): id(idcont){}


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

void Boid::compile_vertexes(){
	/*Boid::boid = glGenLists(1);
	glNewList(boid, GL_COMPILE);
		glBegin(GL_TRIANGLES);
			/*glVertex3f(SCALER*cos(PI*2/3),SCALER*sin(PI*2/3),-2*SCALER);
			glVertex3f(SCALER*cos(PI*4/3),SCALER*sin(PI*4/3),-2*SCALER);
			glVertex3f(SCALER*cos(PI*2),SCALER*sin(PI*2),-2*SCALER);
			
			glVertex3f(SCALER*cos(PI*2/3),SCALER*sin(PI*2/3),-2*SCALER);
			glVertex3f(SCALER*cos(PI*4/3),SCALER*sin(PI*4/3),-2*SCALER);
			glVertex3f(0,0,3*SCALER);
			
			glVertex3f(SCALER*cos(PI*4/3),SCALER*sin(PI*4/3),-2*SCALER);
			glVertex3f(SCALER*cos(PI*2),SCALER*sin(PI*2),-2*SCALER);
			glVertex3f(0,0,3*SCALER);
			
			glVertex3f(SCALER*cos(PI*2),SCALER*sin(PI*2),-2*SCALER);
			glVertex3f(SCALER*cos(PI*2/3),SCALER*sin(PI*2/3),-2*SCALER);
			glVertex3f(0,0,3*SCALER);
			glVertex3f(SCALER,0,0);
			glVertex3f(-SCALER,0,0);
			glVertex3f(0,8*SCALER,0);
			
		
		glEnd();
	glEndList();*/
	InitMesh();
}

#include <iostream>
using namespace std;
void Boid::draw(){
	const static Vetor z_axis(0,0,1);
	const static Vetor y_axis(0,1,0);
	Vetor rotation_axis = produto_vetorial(coordenadas, -y_axis);
	double escalar = produto_escalar(coordenadas, -y_axis);
		
	double rotation_angle = asin(rotation_axis.norma()/coordenadas.norma());
	if(escalar > 0)rotation_angle = -rotation_angle + PI;
	
	glPushMatrix();			
		glTranslated(coordenadas.x, coordenadas.y, coordenadas.z);
		glRotated(rotation_angle*180.0/PI, rotation_axis.x, rotation_axis.y, rotation_axis.z);
		
		if(velocidade != Vetor(0,0,0)){
			Vetor vel = velocidade;
			vel.normalizar();
			Vetor cord = coordenadas;
			cord.normalizar();
			rotation_axis.normalizar();
			Vetor tangente_planeta = vel - projecao_ortogonal(vel,cord);
			rotation_angle = atan2(produto_vetorial(tangente_planeta, rotation_axis).norma(), produto_escalar(tangente_planeta, rotation_axis)) - PI;
			
			//glRotated(rotation_angle*180.0/PI, cord.x,cord.y,cord.z);
			
		}
		
		DrawMesh(0);
	glPopMatrix();
}

void Boid::debug_velocity(){
	Vetor v = velocidade;
	v.normalizar();
	v*=5;
	glPushMatrix();
		glTranslated(coordenadas.x, coordenadas.y, coordenadas.z);
		glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(v.x, v.y, v.y);
		glEnd();
	glPopMatrix();
}

void Boid::debug_acceleration(){
	
}
