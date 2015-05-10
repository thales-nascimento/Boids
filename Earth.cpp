#include "Earth.hpp"



void Earth::gravidade(){
	for(list<Boid>::iterator i = boid_container.boids.begin(); i != boid_container.boids.end(); i++){
		(*i).velocidade -= K_GRAVIDADE/(*i).coordenadas.norma()*(*i).coordenadas; 
	}
}

void Earth::refresh(){
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
	angulo_rotacao += 1.0/30.0/PERIODO_ROTACAO;
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES );	
	glColor3ub(0xff,0xff,0xff);
	
	glPushMatrix();
		glRotated(angulo_rotacao*180/PI,0,0.917060074363,0.398749068974);	//inclinacao 23.5 graus do eixo y em relacao ao z
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



