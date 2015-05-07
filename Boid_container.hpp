#ifndef __BOID_CONTAINER_HPP__
#define __BOID_CONTAINER_HPP__

#include "Boid.hpp"
#include "Vetor.hpp"
#include "Earth.h"

#include <iostream>
#include <GL/freeglut.h>
#include <list>
#include <algorithm>
#include <cstdlib>
using namespace std;

//constantes das forças atuantes nos boids
#define K_COESAO 1
#define K_REPULSAO 5
#define K_ALINHAMENTO 2
#define K_LIDERANCA 1


class Boid_container{
private:
	list<Boid> boids;
	Boid lider;
	
	list<Boid*> esfera_visao(Boid& atual,float multiplicador, list<Boid*> &visiveis);
	
	void lideranca();
	static Vetor altura_pd(Vetor altura);
	
	static constexpr double KP = .01;
	static constexpr double KD = .003;
	static constexpr int H_SETPOINT = SPHERE_RADIUS+3;
	
public:

	Boid_container(Boid leader);	
	
	Boid& operator[](unsigned int indice);
	
	void add_boid(double x, double y, double z);
	void add_boid(int min_dis, int max_dist);
	void remove_boid();
	
	void refresh_boids();
	void draw_boids();
	void print_boids();
};

#endif
