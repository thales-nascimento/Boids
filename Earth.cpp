#include "Earth.hpp"



void Earth::gravidade(){
	for(list<Boid>::iterator i = boid_container.boids.begin(); i != boid_container.boids.end(); i++){
		(*i).velocidade -= K_GRAVIDADE/(*i).coordenadas.norma()*(*i).coordenadas; 
	}
}

void Earth::rotacionar(){	
	for(list<Boid>::iterator i = boid_container.boids.begin(); i!= boid_container.boids.end(); i++){
		double x = (*i).coordenadas.x;
		double y = (*i).coordenadas.y;
		double z = (*i).coordenadas.z;
		x = sin(angulo_rotacao)*(x*0.3987490689264 + y*0.9170600743845) + cos(angulo_rotacao)*z;
		y = x*0.9170600743845 - y*0.3987490689264;
		z = cos(angulo_rotacao)*(x*0.3987490689264 + y*0.9170600743845) - sin(angulo_rotacao)*z;
		(*i).coordenadas.x = x;
		(*i).coordenadas.y = y;
		(*i).coordenadas.z = z;
	}
}

void Earth::refresh(){
	angulo_rotacao += 1.0/30.0/PERIODO_ROTACAO;
	gravidade();
	boid_container.refresh_boids();
}

GLuint Earth::esfera=0;
void Earth::compile_vertexes(){
	esfera = glGenLists(1);
	
	glNewList(esfera, GL_COMPILE);
		glBegin(GL_QUADS);
			double phi=0, theta=0;
			for(int i=0;i<LATITUDES;i++){
				for(int j=0;j<LONGITUDES-1;j++){
					//z sin theta
					glVertex3d(RAIO_TERRESTRE*cos(phi)*cos(theta), RAIO_TERRESTRE*sin(phi) ,RAIO_TERRESTRE*cos(phi)*sin(theta));
					theta += (PI*2/LATITUDES);
					glVertex3d(RAIO_TERRESTRE*cos(phi)*cos(theta), RAIO_TERRESTRE*sin(phi) ,RAIO_TERRESTRE*cos(phi)*sin(theta));
					phi += (PI*2/LONGITUDES);
					glVertex3d(RAIO_TERRESTRE*cos(phi)*cos(theta), RAIO_TERRESTRE*sin(phi) ,RAIO_TERRESTRE*cos(phi)*sin(theta));
					theta -= (PI*2/LATITUDES);				
					glVertex3d(RAIO_TERRESTRE*cos(phi)*cos(theta), RAIO_TERRESTRE*sin(phi) ,RAIO_TERRESTRE*cos(phi)*sin(theta));
				}
				theta += (PI*2/LATITUDES);
			}
		glEnd();
	glEndList();
}

void Earth::earth_draw(){
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES );	
	glColor3ub(0xff,0xff,0xff);
	
	glPushMatrix();
		glRotated(23.5,0,0,1);
		glRotated(angulo_rotacao*180/PI,0,1,0);
		glCallList(esfera);
		boid_container.draw_boids();
	glPopMatrix();
}

void Earth::sun_draw(){
	angulo_translacao_solar += 1.0/30.0/PERIODO_TRANSLACAO;
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES );
	glColor3ub(0xff,0xff,0x79);
	
	glPushMatrix();
		glTranslated(-149.6*RAIO_TERRESTRE*cos(angulo_translacao_solar),0,-149.6*RAIO_TERRESTRE*sin(angulo_translacao_solar));
		glScaled(6.388073,6.388073,6.388073);
		glCallList(esfera);
	glPopMatrix();
}


void Earth::earth_debug(){
	glBegin(GL_LINES);
		glColor3ub(0xff,0,0);
		glVertex3i(RAIO_TERRESTRE*2048,0,0);
		glVertex3i(-RAIO_TERRESTRE*2048,0,0);
		glColor3ub(0,0,0xff);
		glVertex3i(0,RAIO_TERRESTRE*2048,0);
		glVertex3i(0,-RAIO_TERRESTRE*2048,0);
		glColor3ub(0,0xff,0);
		glVertex3i(0,0,RAIO_TERRESTRE*2048);
		glVertex3i(0,0,-RAIO_TERRESTRE*2048);
	glEnd();
}

Earth::Earth(){
	angulo_rotacao=0;
	angulo_translacao_solar=0;
}

