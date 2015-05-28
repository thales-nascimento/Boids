#ifndef __BOID_CONTAINER_HPP__
#define __BOID_CONTAINER_HPP__

#include "Boid.hpp"
#include "esfera.h"

#include <iostream>
#include <GL/freeglut.h>
#include <list>
#include <cstdlib>
using namespace std;

//constantes das forças atuantes nos boids
#define K_COESAO 3
#define K_REPULSAO 1.5
#define K_ALINHAMENTO 7.0
#define K_LIDERANCA 1

#define K_DIRECIONAMENTO 1
#define INFLUENCIA_LIDER 14

class Planeta;

class Boid_container{
friend class Planeta;
private:
	list<Boid> boids;
	
	Boid *lider=NULL;
	void liderar();
	Vetor setpoint;
	
	void esfera_visao(Boid& atual,float multiplicador, list<Boid*> &visiveis);
	
	int max_height;
	int min_height;
	
public:	

	void set_point(double theta, double phi, double rotacao);

	void define_atmosfera(int bottom, int top);
	
	void add_boid(double x, double y, double z);
	void add_boid_rand();
	void remove_boid_rand();
	Boid* operator[](unsigned int i);
	
	void designa_lider(unsigned int id);
	void toggle_setpoint();
	
	void refresh_boids();
	void draw_boids();
	void print_boids();
	
	unsigned int get_n_boids();
	
	
};

#endif
