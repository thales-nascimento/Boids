#ifndef __BOID_CONTAINER_HPP__
#define __BOID_CONTAINER_HPP__

#include "Boid.hpp"
#include "Vetor.hpp"
#include "consts.h"

#include <iostream>
#include <GL/freeglut.h>
#include <list>
#include <algorithm>
#include <cstdlib>
using namespace std;


class Boid_container{
private:
	list<Boid> boids;
	Boid lider;
	
	//list<Boid*> esfera_visao(Boid& atual);
	
	void coesao();
	void repulsao();
	void alinhamento();
	void lideranca();
	
public:
	list<Boid*> esfera_visao(Boid& atual);

	Boid_container(Boid leader);	
	
	Boid& operator[](unsigned int indice);
	
	void add_boid();
	void add_boid(double x, double y, double z);
	void remove_boid();
	
	void refresh_boids();
	void draw_boids();
	void print_boids();
};

#endif
