#ifndef __BOTAO_HPP_INCLUDED__
#define __BOTAO_HPP_INCLUDED__


#define BOTAO_TEXTO 0
#define BOTAO_NORMAL 1
#define BOTAO_SELECIONADO 2
#define BOTAO_CLICADO 3

#define NO_ACTION 0
#define INCREMENTA_BOIDS 1
#define DECREMENTA_BOIDS -1
#define PROXIMO_BOID 2
#define BOID_ANTERIOR -2
#define PROXIMA_CAMERA 3
#define CAMERA_ANTERIOR -3
#define PLANETA_ANTERIOR -4
#define PROXIMO_PLANETA 4
#define PROXIMO_LIDER 5
#define LIDER_ANTERIOR -5


class botao{
	public:
	char* texto;
	
	int x0, y0;
	int x1, y1;
	
	int status;
	int funcao;
	
	static const unsigned char default_r=0x3f, default_g=0x3f, default_b=0x3f;
	static const unsigned char hover_r=0x79,hover_g=0xff,hover_b=0x79;
	static const unsigned char click_r=0xff, click_g=0xff, click_b=0x79;
	
	botao(){
		status = BOTAO_NORMAL;
	}
	
};

#endif
