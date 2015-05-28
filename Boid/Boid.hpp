#ifndef __BOID_HPP_INCLUDED__
#define __BOID_HPP_INCLUDED__

extern "C"{
#include "blender_model_importer.h"
}

#include "../esfera.h"
#include "../Vetor.hpp"
#include <GL/gl.h>
#include <cmath>
#include <cstdlib>
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
	
	Vetor get_coordenadas();
	Vetor get_aceleracao();
	Vetor get_velocidade();	
	
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
