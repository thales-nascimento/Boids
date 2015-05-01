#ifndef __VETOR_HPP_INCLUDED__
#define __VETOR_HPP_INCLUDED__

#include <cmath>

class Vetor{
	public:
	double x,y,z;
	const static unsigned int size = 3;
	
	double& operator[](unsigned int i);
	
	double norma();
	void normalizar();
	
	Vetor(double x0, double y0, double z0, double x1, double y1, double z1);
	Vetor();
	Vetor(double x, double y, double z);
};

bool operator !=(Vetor v, Vetor w);
bool operator ==(Vetor v, Vetor w);

Vetor operator *(double k, Vetor v);
Vetor operator *(Vetor v, double k);

Vetor operator +(Vetor v, Vetor w);
Vetor operator-(Vetor v, Vetor w);
Vetor operator-(Vetor v);

void operator +=(Vetor& v, Vetor w);
void operator -=(Vetor& v, Vetor w);
void operator *=(Vetor& v, double k);

Vetor produto_vetorial(Vetor v, Vetor w);
double produto_escalar(Vetor v, Vetor w);

#endif
