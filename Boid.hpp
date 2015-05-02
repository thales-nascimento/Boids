#ifndef __BOID_HPP_INCLUDED__
#define __BOID_HPP_INCLUDED__
#include "Vetor.hpp"


class Boid {
private:
	Vetor coordenadas;
	Vetor velocidade;
	Vetor aceleracao;
	
	void acelerar();
	void mover();
public:
	constexpr static double VELOCIDADE_MAX = .32;
	constexpr static double ACELERACAO_MAX = .08;
	constexpr static double CAMPO_DE_VISAO = 8;

	void mudar_aceleracao(Vetor a);
	
	void refresh();
	
	Boid();
	Boid(double x, double y, double z);
	Boid(Vetor posicao);
	
	Vetor get_coordenadas();
	Vetor get_aceleracao();
	Vetor get_velocidade();
};

#endif
