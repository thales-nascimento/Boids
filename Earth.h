#ifndef __EARTH_H_INCLUDED__
#define __EARTH_H_INCLUDED__

#include <GL/gl.h>
#include <math.h>
#include "PI.h"

#define SPHERE_RADIUS 128
#define LATITUDES 15
#define LONGITUDES 15


void earth_init();
void earth_draw();
void earth_debug();


#endif
