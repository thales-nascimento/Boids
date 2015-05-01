#include "Vetor.hpp"

double& Vetor::operator[](unsigned int i){
	switch(i){
		case 0: return x;
		case 1: return y;
		case 2: return z;
	}
}

double Vetor::norma(){
	double soma = x*x + y*y + z*z;
	return sqrt(soma);
}

void Vetor::normalizar(){
	double norma = this->norma();
	if(norma == 0)return;
	x /= norma;
	y /= norma;
	z /= norma;
}

Vetor::Vetor(double x0, double y0, double z0, double x1, double y1, double z1){
	x = x1-x0;
	y = y1-y0;
	z = z1-z0;
}

Vetor::Vetor(){
	x = 0;
	y = 0;
	z = 0;	
}
Vetor::Vetor(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}


bool operator ==(Vetor v, Vetor w){
	for(unsigned int i=0;i<v.size;i++){
		if(v[i] != w[i])return false;
	}
	return true;
}
bool operator !=(Vetor v, Vetor w){
	return !(v == w);
}

Vetor operator *(double k, Vetor v){
	Vetor w;
	for(unsigned int i=0;i<v.size;i++){
		w[i] = k*v[i];
	}
	return w;
}
Vetor operator *(Vetor v, double k){
	return k*v;
}

Vetor operator +(Vetor v, Vetor w){
	Vetor u;
	for(unsigned int i=0;i<u.size;i++){
		u[i] = v[i] + w[i];
	}
	return u;
}
Vetor operator-(Vetor v, Vetor w){
	return v + (-1*w);
}
Vetor operator-(Vetor v){
	return -1*v;
}

void operator +=(Vetor& v, Vetor w){
	v = v+w;
}
void operator -=(Vetor& v, Vetor w){
	v = v-w;
}
void operator *=(Vetor& v, double k){
	v = k*v;
}

Vetor produto_vetorial(Vetor v, Vetor w){
	Vetor u(v[1]*w[2] - v[2]*w[1], v[0]*w[2] - v[2]*w[0], v[0]*w[1] - v[1]*w[0]);
	return u;
}
double produto_escalar(Vetor v, Vetor w){
	return v[0]*w[0] + v[1]*w[1] + v[2]*w[2];
}

