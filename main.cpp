#include <GL/freeglut.h>
#include <cmath>
#include "Boid_container.hpp"
#include "consts.h"

int main(){
	Boid lider(0,0,0);
	Boid_container container(lider);
	container.add_boid(0,0,1);
	container.add_boid(1,1,1);
	container.add_boid(1,0,1);
	container.add_boid(0,1,1);
	
	
	
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	container.print_boids();
	container.refresh_boids();
	cout<<"_____________________\n";
	
}

