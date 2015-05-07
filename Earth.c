#include "Earth.h"

GLuint esfera;
void earth_init(){
	esfera = glGenLists(1);
	
	glNewList(esfera, GL_COMPILE);
		glBegin(GL_QUADS);
			
			glColor3ub(0xff,0xff,0xff);
			double phi=0, theta=0;
			for(int i=0;i<LATITUDES;i++){
				for(int j=0;j<LONGITUDES-1;j++){
					//z sin theta
					glVertex3d(SPHERE_RADIUS*cos(phi)*cos(theta), SPHERE_RADIUS*sin(phi) ,SPHERE_RADIUS*cos(phi)*sin(theta));
					theta += (PI*2/LATITUDES);
					glVertex3d(SPHERE_RADIUS*cos(phi)*cos(theta), SPHERE_RADIUS*sin(phi) ,SPHERE_RADIUS*cos(phi)*sin(theta));
					phi += (PI*2/LONGITUDES);
					glVertex3d(SPHERE_RADIUS*cos(phi)*cos(theta), SPHERE_RADIUS*sin(phi) ,SPHERE_RADIUS*cos(phi)*sin(theta));
					theta -= (PI*2/LATITUDES);				
					glVertex3d(SPHERE_RADIUS*cos(phi)*cos(theta), SPHERE_RADIUS*sin(phi) ,SPHERE_RADIUS*cos(phi)*sin(theta));
				}
				theta += (PI*2/LATITUDES);
			}
		glEnd();
	glEndList();
}

void earth_draw(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES );
	glCallList(esfera);
}

void earth_debug(){
	glBegin(GL_LINES);
		glColor3ub(0xff,0,0);
		glVertex3i(SPHERE_RADIUS*10,0,0);
		glVertex3i(-SPHERE_RADIUS*10,0,0);
		glColor3ub(0,0,0xff);
		glVertex3i(0,SPHERE_RADIUS*10,0);
		glVertex3i(0,-SPHERE_RADIUS*10,0);
		glColor3ub(0,0xff,0);
		glVertex3i(0,0,SPHERE_RADIUS*10);
		glVertex3i(0,0,-SPHERE_RADIUS*10);
	glEnd();
}
