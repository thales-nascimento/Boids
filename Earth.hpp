#ifndef __EARTH_HPP_INCLUDED__
#define __EARTH_HPP_INCLUDED__

#define K_GRAVIDADE .01
#define PERIODO_ROTACAO 48.0
#define PERIODO_TRANSLACAO 17520

#include "esfera.h"

#include <GL/gl.h>
#include <math.h>
#include "PI.h"
#include "Boid_container.hpp"


class Earth{
private:
	double angulo_rotacao=0;
	void gravidade();
	
	double angulo_translacao_solar=0;
	
public:

	Boid_container boid_container;

	static GLuint esfera;
	static void compile_vertexes();
	void earth_draw();
	void earth_debug();
	void sun_draw();
	
	void refresh();

};

#endif
