#include "Hud.hpp"
int Hud::hover_buttons(int x, int y, bool clicado){
	y = height - y;
	
	for(int i=0;i<botoes.size();i++){
		if(botoes[i].status > BOTAO_NORMAL)botoes[i].status = BOTAO_NORMAL;
		if(x >= botoes[i].x0*width/100.0 && x <= botoes[i].x0*width/100.0 + botoes[i].x1){
			if(y >= botoes[i].y0*height/100.0 && y <= botoes[i].y0*height/100.0 + botoes[i].y1){
				if(clicado){
					botoes[i].status = BOTAO_CLICADO;
					return botoes[i].funcao;
				}else botoes[i].status = BOTAO_SELECIONADO;
			}
		}
	}
	return NO_ACTION;
}

unsigned int Hud::add_string(float x0, float y0, char* s){
	botao b;
	b.x0 = x0;
	b.y0 = y0;
	b.x1 = 0;
	b.y1 = 0;
	b.texto = s;
	b.status = BOTAO_TEXTO;
	botoes.push_back(b);
	return botoes.size()-1;
}

void Hud::set_string(unsigned int posicao, char* novo_texto){
	botoes[posicao].texto = novo_texto;
}

void Hud::add_button(float x0, float y0, int f, char* texto){
	botao b;
	b.x0 = x0;
	b.y0 = y0;
	b.x1 = 10*strlen(texto);	//10 é a largura das letras utilizadas
	b.y1 = 13;			//13 é a altura das letras da fonte utilizada
	b.funcao = f;
	b.texto = texto;
	botoes.push_back(b);
}

Hud::Hud(double w, double h){
	width = w;
	height = h;
}


void Hud::draw(){
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			glViewport(0,0,width,height);
			glOrtho(0,width,0,height,-1,1);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	
	for(int i=0;i<botoes.size();i++){
		switch(botoes[i].status){
			case BOTAO_SELECIONADO: glColor3ub(botoes[i].hover_r,botoes[i].hover_g,botoes[i].hover_b);
			break;
			case BOTAO_CLICADO: glColor3ub(botoes[i].click_r,botoes[i].click_g,botoes[i].click_b);
			break;
			
			default: glColor3ub(botoes[i].default_r,botoes[i].default_g,botoes[i].default_b);
		}
		
		if(botoes[i].status>BOTAO_TEXTO){
			glBegin(GL_QUADS);
				glVertex2i(botoes[i].x0/100.0*width, botoes[i].y0/100.0*height);
				glVertex2i(botoes[i].x0/100.0*width, botoes[i].y0/100.0*height + botoes[i].y1);
				glVertex2i(botoes[i].x0/100.0*width + botoes[i].x1, botoes[i].y0/100.0*height + botoes[i].y1);
				glVertex2i(botoes[i].x0/100.0*width + botoes[i].x1, botoes[i].y0/100.0*height);
			glEnd();
		}
		glColor3ub(0xff,0xff,0xff);
		glRasterPos2i(botoes[i].x0/100.0*width, botoes[i].y0/100.0*height+2);
		for(unsigned int j=0;botoes[i].texto[j]!=0;j++){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, botoes[i].texto[j]);
		}
	}
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
}
