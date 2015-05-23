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
	Boid();
	
}

Boid::Boid(Vetor posicao): id(idcont){
	coordenadas = posicao;
	Boid();
}


Boid::Boid(): id(idcont){
	vizinhos_vistos=0;
}


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
			glVertex3f(0,0,3*SCALER);*/
			glVertex3f(SCALER,0,-SCALER);
			glVertex3f(-SCALER,0,-SCALER);
			glVertex3f(0,0,SCALER);
			
		
		glEnd();
	glEndList();
}

void Boid::draw(){
	const static Vetor z_axis(0,0,1);
	Vetor rotation_axis = produto_vetorial(velocidade, z_axis);
	
	double rotation_angle;
	
	if(rotation_axis.norma() == .0){
		if(velocidade.z < 0){
			rotation_angle = PI;
			rotation_axis.y = 1;
		}
	} else if(velocidade.norma() != .0){
		rotation_angle = asin(rotation_axis.norma()/velocidade.norma());
		
		if(velocidade.z < .0){
			rotation_axis.x = -rotation_axis.x;
			rotation_axis.y = -rotation_axis.y;
			rotation_angle += PI;
		}
	} else {
		rotation_angle = .0;
	}
	
	
	glPushMatrix();
		glTranslated(coordenadas.x, coordenadas.y, coordenadas.z);
		glRotated(rotation_angle*180/PI,-rotation_axis.x,rotation_axis.y,rotation_axis.z);
		
		glCallList(Boid::boid);
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
