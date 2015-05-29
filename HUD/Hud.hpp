#ifndef __HUD_HPP_INCLUDED__
#define __HUD_HPP_INCLUDED__

#include "botao.hpp"

#include <string.h>
#include <GL/freeglut.h>
#include <vector>

using namespace std;

class Hud {
private:
	vector<botao> botoes;
	double width, height;
	
public:
	Hud(double w, double h);

	unsigned int add_string(float x0, float y0, char* s);
	void set_string(unsigned int posicao, char* novo_texto);
	void add_button(float x0, float y0, int funcao, char* texto);

	int hover_buttons(int x, int y, bool clicado);
	void draw();
};

#endif
