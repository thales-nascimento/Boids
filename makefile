CC = g++

all: Boid.o Boid_container.o Vetor.o Planeta.o observer.o Hud.o blender_model_importer.o main.cpp
	$(CC) -o boids Boid.o Boid_container.o Vetor.o Planeta.o observer.o Hud.o blender_model_importer.o main.cpp -lGL -lglut -lm -lGLU

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

Hud.o:
	$(CC) -c -o Hud.o HUD/Hud.cpp
	
blender_model_importer.o:
	gcc -c -o blender_model_importer.o blender_model_importer.c
	
clear:
	rm *.o boids
