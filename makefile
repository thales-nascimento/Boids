CC = g++

all: Boid.o Boid_container.o Vetor.o Planeta.o observer.o main.cpp
	$(CC) -o boids Boid.o Boid_container.o Vetor.o Planeta.o observer.o main.cpp -lGL -lglut -lm -lGLU

Vetor.o:
	$(CC) -c -o Vetor.o Vetor.cpp

Boid.o:
	$(CC) -c -o Boid.o Boid.cpp
	
Boid_container.o:
	$(CC) -c -o Boid_container.o Boid_container.cpp
	
Planeta.o:
	$(CC) -c -o Planeta.o Planeta.cpp

observer.o:
	$(CC) -c -o observer.o observer.cpp
	
	
clear:
	rm *.o boids
