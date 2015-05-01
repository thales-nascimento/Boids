#include "Boid.hpp"

Boid::Boid(double x, double y, double z){
	coordenadas[0] = x;
	coordenadas[1] = y;
	coordenadas[2] = z;
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

