#ifndef __BOID_HPP_INCLUDED__
#define __BOID_HPP_INCLUDED__

#include "Vetor.hpp"
#include <GL/gl.h>
#include <cmath>
#include <cstdlib>
#include "PI.h"
#define SCALER 0.25

class Earth;

class Boid {
friend class Earth;
private:
	Vetor coordenadas;
	Vetor velocidade;
	Vetor aceleracao;
	
	void acelerar();
	void mover();
	
public:
	int vizinhos_vistos=0;

	constexpr static double VELOCIDADE_MAX = .1;
	constexpr static double ACELERACAO_MAX = .005;
	constexpr static double CAMPO_DE_VISAO = 3;

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
	
	void debug_velocity();
	void debug_acceleration();
};

#endif
