#ifndef __EARTH_HPP_INCLUDED__
#define __EARTH_HPP_INCLUDED__

#define TAXA_DE_ATUALIZACAO 30

#include "esfera.h"
#include <GL/gl.h>
#include <math.h>
#include "Boid_container.hpp"

#define ATMOSFERA_TOP 3
#define ATMOSFERA_BOT 13


class Planeta{
private:
	unsigned char color[3];
	
	void gravitacionar();
	void transladar();
	
	double angulo_rotacao;
	
	Vetor coordenadas;
public:
	const unsigned int PERIODO_ROTACAO;
	const unsigned int PERIODO_TRANSLACAO;
	const double INCLINACAO_ROT;
	const double K_GRAVIDADE;
	const unsigned int RAIO;

	Boid_container boid_container;

	static GLuint esfera;
	static void compile_vertexes();
	void draw();
	void draw_axis();
	void change_color(unsigned char, unsigned char, unsigned char);
	
	void refresh();
	
	double get_rotation();
	Vetor get_coordenadas();
	
	Planeta(double inclinacao_rotacao, unsigned int periodo_rotacao, unsigned int periodo_translacao, double constante_gravidade, unsigned int raio, int distancia_centro);

	
};

#endif
