CC = g++

all: Boid.o Boid_container.o Vetor.o Earth.o Observer.o main.cpp
	$(CC) -lGL -lglut -lm -lGLU -o boids Boid.o Boid_container.o Vetor.o Earth.o Observer.o main.cpp

Vetor.o:
	$(CC) -c -o Vetor.o Vetor.cpp
	
Boid.o:
	$(CC) -c -o Boid.o Boid.cpp
	
Boid_container.o:
	$(CC) -c -o Boid_container.o Boid_container.cpp
	
Earth.o:
	$(CC) -c -o Earth.o Earth.cpp

Observer.o:
	$(CC) -c -o Observer.o Observer.cpp
	
	
clear:
	rm *.o boids
