#ifndef __OBSERVER_HPP_INCLUDED__
#define __OBSERVER_HPP_INCLUDED__

#include <GL/freeglut.h>
#include <cmath>
#include "Vetor.hpp"
#include "esfera.h"
#include "Planeta.hpp"

extern bool observer_pause;

void observer_look();
void observer_init(Planeta *e);
void observer_change_mode(int mode);


#endif
