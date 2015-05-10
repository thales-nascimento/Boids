CC = g++
CFLAGS = -std=c++11

all: Boid.o Boid_container.o Vetor.o Earth.o main.cpp
	$(CC) $(CFLAGS) -lGL -lglut -lm -lGLU -o boids Boid.o Boid_container.o Vetor.o Earth.o main.cpp

Vetor.o:
	$(CC) $(CFLAGS) -c -o Vetor.o Vetor.cpp
	
Boid.o:
	$(CC) $(CFLAGS) -c -o Boid.o Boid.cpp
	
Boid_container.o:
	$(CC) $(CFLAGS) -c -o Boid_container.o Boid_container.cpp
	
Earth.o:
	$(CC) $(CFLAGS) -c -o Earth.o Earth.cpp

	
	
clear:
	rm *.o boids
