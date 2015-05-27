#ifndef __BOID_HPP_INCLUDED__
#define __BOID_HPP_INCLUDED__

extern "C"{
#include "blender_model_importer.h"
}

#include "Vetor.hpp"
#include <GL/gl.h>
#include <cmath>
#include <cstdlib>
#include "esfera.h"
#define SCALER 0.25

class Planeta;

class Boid {
friend class Planeta;

public:
	const unsigned int id;
	static unsigned int idcont;

	int vizinhos_vistos;

	static double VELOCIDADE_MAX;
	static double ACELERACAO_MAX;
	static double CAMPO_DE_VISAO;

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
	
private:
	Vetor coordenadas;
	Vetor velocidade;
	Vetor aceleracao;
	
	void acelerar();
	void mover();

};

#endif
