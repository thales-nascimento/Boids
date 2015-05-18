#ifndef __OBSERVER_HPP_INCLUDED__
#define __OBSERVER_HPP_INCLUDED__

#include <GL/freeglut.h>
#include <cmath>
#include "Vetor.hpp"
#include "PI.h"
#include "Earth.hpp"

#define FREE_CAMERA 0
#define THIRD_UP 1
#define GEO_ESTACIONARIA 2
#define OBSERVER_SPEED 8

class Observer{
private:
	Vetor posicao;
	Earth *earth;
	
	
public:
	static double theta, phi;
	static bool pause;
	static float distancia;
	static int modo_observacao;

	void look();
	void move();
	
	void init(Earth *e);
	static void change_mode(int mode);
	Observer();
};

#endif
