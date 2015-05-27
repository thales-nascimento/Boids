#ifndef __OBSERVER_HPP_INCLUDED__
#define __OBSERVER_HPP_INCLUDED__

#include <GL/freeglut.h>
#include <cmath>
#include "Vetor.hpp"
#include "esfera.h"
#include "Planeta.hpp"
#include "HUD/Hud.hpp"
#include "string"
#include "stdio.h"

extern bool observer_pause;

void observer_look();
void observer_init(Planeta *e, Hud *h);
void observer_change_mode(int mode);


#endif
