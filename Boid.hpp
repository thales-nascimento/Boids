#ifndef __BOID_HPP_INCLUDED__
#define __BOID_HPP_INCLUDED__

#include "Vetor.hpp"
#include <GL/gl.h>
#include <cmath>
#include <cstdlib>

#define PI 3.14159265358979
#define SCALER 0.5

class Boid {
private:
	Vetor coordenadas;
	Vetor velocidade;
	Vetor aceleracao;
	
	void acelerar();
	void mover();
	
public:

	constexpr static double VELOCIDADE_MAX = .1;
	constexpr static double ACELERACAO_MAX = .01;
	constexpr static double CAMPO_DE_VISAO = 2;

	void mudar_aceleracao(Vetor a);
	
	void refresh();
	
	Boid();
	Boid(double x, double y, double z);
	Boid(Vetor posicao);
	
	Vetor get_coordenadas();
	Vetor get_aceleracao();
	Vetor get_velocidade();
	
	
	static GLuint boid;	//variavel que armazena o identificador da lista de vértices do boid
	static void compile_vertexes();
	void draw();
};

#endif
