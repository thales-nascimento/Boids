#include "Boid_container.hpp"

//sort functions
bool sort_x(Boid a, Boid b){
	return a.get_coordenadas().x < b.get_coordenadas().x;
}

bool sort_y(Boid *a, Boid *b){
	return a->get_coordenadas().y < b->get_coordenadas().y;
}

bool sort_z(Boid *a, Boid *b){
	return a->get_coordenadas().z < b->get_coordenadas().z;
}




//adicionar e remover boids

void Boid_container::add_boid(double x, double y, double z){
	boids.emplace(boids.end(), x, y, z);
}

void Boid_container::add_boid(int min_dist, int max_dist){
	Vetor aleatorio((signed short)rand(),(signed short)rand(),(signed short)rand());
	aleatorio.normalizar();
	int tamanho = rand()%(max_dist-min_dist)+min_dist;
	aleatorio *=tamanho;
	add_boid(aleatorio.x, aleatorio.y,aleatorio.z);
}

void Boid_container::remove_boid(){
	if(boids.empty())return;
	list<Boid>::iterator i = boids.begin();
	advance(i, rand()%boids.size());			//remover um boid aleatório
	boids.erase(i);
	
}


//atualização


void Boid_container::refresh_boids(){
	for(list<Boid>::iterator boid_atual = boids.begin(); boid_atual != boids.end(); boid_atual++){
		list<Boid*> visiveis;
		Vetor aceleracao;
		Vetor altura = (*boid_atual).get_coordenadas();
		Vetor versor_altura = altura;
		versor_altura.normalizar();
		
		if(H_SETPOINT-altura.norma() > 0){
			aceleracao += (sqrt(H_SETPOINT-altura.norma())*versor_altura);
		}else {
			aceleracao -= (sqrt(-H_SETPOINT+altura.norma())*versor_altura);
		}
		
		switch((*boid_atual).vizinhos_vistos){
			case 0: esfera_visao(*boid_atual,5, visiveis);
			break;
			case 1: esfera_visao(*boid_atual,2.5, visiveis);
			break;
			default: esfera_visao(*boid_atual,1,visiveis);
		}
		(*boid_atual).vizinhos_vistos = visiveis.size();
		
		
		Vetor repulsao, alinhamento, coesao;
		for(list<Boid*>::iterator boid_atuante = visiveis.begin(); boid_atuante != visiveis.end(); boid_atuante++){
			Vetor distancia = (*boid_atuante)->get_coordenadas() - (*boid_atual).get_coordenadas();
			double norma = distancia.norma();
			coesao += distancia;
			repulsao -= (1.0/norma/norma)*distancia;
			alinhamento += norma*(*boid_atuante)->get_velocidade();
		}
		
		repulsao *= K_REPULSAO;
		aceleracao += repulsao;
		if(aceleracao.norma() > K_REPULSAO){
			(*boid_atual).mudar_aceleracao(aceleracao);
			continue;
		}
		
		coesao *= K_COESAO;
		aceleracao += coesao;
		alinhamento *= K_ALINHAMENTO;
		aceleracao += alinhamento;
		(*boid_atual).mudar_aceleracao(aceleracao);
	}
	
	for(list<Boid>::iterator atual = boids.begin(); atual != boids.end(); ++atual){
		(*atual).refresh();
	}
}


void decide(){
	
}

void Boid_container::esfera_visao(Boid& atual, float multiplicador, list<Boid*> &cubo){
	
	double x0 = atual.get_coordenadas().x - Boid::CAMPO_DE_VISAO*multiplicador;
	double x1 = atual.get_coordenadas().x + Boid::CAMPO_DE_VISAO*multiplicador;
	double y0 = atual.get_coordenadas().y - Boid::CAMPO_DE_VISAO*multiplicador;
	double y1 = atual.get_coordenadas().y + Boid::CAMPO_DE_VISAO*multiplicador;
	double z0 = atual.get_coordenadas().z - Boid::CAMPO_DE_VISAO*multiplicador;
	double z1 = atual.get_coordenadas().z + Boid::CAMPO_DE_VISAO*multiplicador;
	
	list<Boid>::iterator iterador;
	list<Boid*>::iterator sub_iterador;
	int inicio, fim, meio, posicao;
	
	//selecionar um "cubo de visao"
	
	//selecionar no eixo x
	//sort
	boids.sort(sort_x);
	//obter o menor x maior ou igual a x0
	int borda_menor=0, borda_maior=0;
	inicio = 0, posicao=0;
	fim = boids.size();
	iterador = boids.begin();
	while(fim >= inicio){
		meio = (inicio + fim)/2;
		advance(iterador, meio-posicao);
		posicao = borda_menor = meio;
		if((*iterador).get_coordenadas().x < x0){
			inicio = meio + 1;
		} else  if((*iterador).get_coordenadas().x > x0){
			fim = meio -1;
		} else {
			break;
		}
	}
	if(iterador != boids.end() && (*iterador).get_coordenadas().x < x0){
		borda_menor++;
	}
	
	//obter maior x menor ou igual a x1
	inicio = 0;
	fim = boids.size();
	while(fim >= inicio){
		meio = (inicio+fim)/2;
		advance(iterador, meio-posicao);
		posicao = borda_maior = meio;
		if((*iterador).get_coordenadas().x > x1){
			fim = meio - 1;
		} else  if((*iterador).get_coordenadas().x < x1){
			inicio = meio +1;
		} else {
			break;
		}
	}
	if(iterador != boids.begin() && (*iterador).get_coordenadas().x > x1){
		borda_maior--;
	}
	//selecionar os boids dentro do intervalo [x0, x1]
	advance(iterador, borda_maior-posicao);
	posicao = borda_maior;
	for(int i = borda_maior;i>=borda_menor;i--){
		if((*iterador).get_coordenadas() != atual.get_coordenadas()){	//eliminando a si mesmo da lista
			cubo.push_back(&(*iterador));
		}
		iterador--;
		posicao--;
	}
	
	//selecionar no eixo y
	//sort
	cubo.sort(sort_y);
	//obter maior y menor que y0
	borda_maior = borda_menor = 0;
	sub_iterador = cubo.begin();
	posicao = 0;
	inicio = 0;
	fim = cubo.size();
	while(fim >= inicio){
		meio = (inicio + fim)/2;
		if(meio < cubo.size()){
			advance(sub_iterador, meio-posicao);
			posicao = borda_menor = meio;
		} else {
			break;
		}
		if((*sub_iterador)->get_coordenadas().y < y0){
			inicio = meio + 1;
		} else  if((*sub_iterador)->get_coordenadas().y > y0){
			fim = meio -1;
		} else {
			break;
		}
	}
	if(sub_iterador != cubo.end() && (*sub_iterador)->get_coordenadas().y < y0){
		borda_menor++;
		posicao++;
	}
	//obter maior y menor ou igual a y1
	inicio = 0;
	fim = cubo.size();
	while(fim >= inicio){
		meio = (inicio + fim)/2;
		if(meio < cubo.size()){
			advance(sub_iterador, meio-posicao);
			posicao = borda_maior = meio;
		} else {
			break;
		}
		if((*sub_iterador)->get_coordenadas().y < y1){
			inicio = meio + 1;
		} else  if((*sub_iterador)->get_coordenadas().y > y1){
			fim = meio -1;
		} else {
			break;
		}
	}
	if(sub_iterador != cubo.begin() && (*sub_iterador)->get_coordenadas().y > y1){
		borda_maior--;
	}
	
	//eliminar os boids fora do intervalo [y0, y1]
	if(borda_maior < cubo.size()){
		advance(sub_iterador, borda_maior+1 -posicao);
		cubo.erase(sub_iterador, cubo.end());
	}
	if(borda_menor > 0){
		sub_iterador = cubo.begin();
		advance(sub_iterador, borda_menor);
		cubo.erase(cubo.begin(),sub_iterador);
	}
	//selecionar no eixo z
	//sort
	cubo.sort(sort_z);
	//obter maior z menor que z0
	borda_maior = borda_menor = 0;
	sub_iterador = cubo.begin();
	posicao = 0;
	inicio = 0;
	fim = cubo.size();
	while(fim >= inicio){
		meio = (inicio + fim)/2;
		if(meio < cubo.size()){
			advance(sub_iterador, meio-posicao);
			posicao = borda_menor = meio;
		} else {
			break;
		}
		if((*sub_iterador)->get_coordenadas().z < z0){
			inicio = meio + 1;
		} else  if((*sub_iterador)->get_coordenadas().z > z0){
			fim = meio -1;
		} else {
			break;
		}
	}
	if(sub_iterador != cubo.end() && (*sub_iterador)->get_coordenadas().z < z0){
		borda_menor++;
		posicao++;
	}
	//obter maior z menor ou igual a z1
	inicio = 0;
	fim = cubo.size();
	while(fim >= inicio){
		meio = (inicio + fim)/2;
		if(meio < cubo.size()){
			advance(sub_iterador, meio-posicao);
			posicao = borda_maior = meio;
		} else {
			break;
		}
		if((*sub_iterador)->get_coordenadas().z < z1){
			inicio = meio + 1;
		} else  if((*sub_iterador)->get_coordenadas().z > z1){
			fim = meio -1;
		} else {
			break;
		}
	}
	if(sub_iterador != cubo.begin() && (*sub_iterador)->get_coordenadas().z > z1){
		borda_maior--;
	}
	
	//eliminar os boids fora do intervalo [z0, z1]
	if(borda_maior < cubo.size()){
		advance(sub_iterador, borda_maior+1 -posicao);
		cubo.erase(sub_iterador, cubo.end());
	}
	if(borda_menor > 0){
		sub_iterador = cubo.begin();
		advance(sub_iterador, borda_menor);
		cubo.erase(cubo.begin(),sub_iterador);
	}
	
	//filtrar brutamente para circulo
	sub_iterador = cubo.begin();
	Vetor distancia;
	while(sub_iterador != cubo.end()){
		distancia = (*sub_iterador)->get_coordenadas() - atual.get_coordenadas();
		if(distancia.norma() > Boid::CAMPO_DE_VISAO*multiplicador){
			sub_iterador = cubo.erase(sub_iterador);
		} else {
			sub_iterador++;
		}
	}
}



//output
void Boid_container::print_boids(){
	for(list<Boid>::iterator atual = boids.begin(); atual != boids.end(); ++atual){
		cout<<(*atual).get_coordenadas().x<<"	"<<(*atual).get_coordenadas().y<<"	"<<(*atual).get_coordenadas().z<<"	|	"<<(*atual).get_aceleracao().norma()<<"	"<<(*atual).get_velocidade().norma()<<endl;
	}
}

void Boid_container::draw_boids(){
	Vetor local;
	for(list<Boid>::iterator atual = boids.begin(); atual != boids.end(); ++atual){
		(*atual).draw();
	}
}


