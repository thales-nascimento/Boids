#ifndef __BOID_CONTAINER_HPP__
#define __BOID_CONTAINER_HPP__

#include "Boid.hpp"
#include "esfera.h"

#include <iostream>
#include <GL/freeglut.h>
#include <list>
#include <algorithm>
#include <cstdlib>
using namespace std;

//constantes das forças atuantes nos boids
#define K_COESAO 1.5
#define K_REPULSAO 1.5
#define K_ALINHAMENTO 7.0
#define K_LIDERANCA 1

class Planeta;

class Boid_container{
friend class Planeta;
private:
	list<Boid> boids;
	Boid lider;
	
	void esfera_visao(Boid& atual,float multiplicador, list<Boid*> &visiveis);
	
	void lideranca();	
	int max_height;
	int min_height;
	
public:	
	void define_atmosfera(int bottom, int top);
	
	void add_boid(double x, double y, double z);
	void add_boid_rand();
	void remove_boid();
	
	void refresh_boids();
	void draw_boids();
	void print_boids();
	
	Boid *procurar_boid(unsigned int id);
	
};

#endif
