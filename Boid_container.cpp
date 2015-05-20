#include "Boid_container.hpp"

bool sort_id(Boid a, Boid b){
	return a.id < b.id;
}

//acesso aos boids
Boid* Boid_container::procurar_boid(unsigned int id){
	boids.sort(sort_id);
	list<Boid>::iterator i= boids.begin();
	int inicio = 0;
	int posicao=0;
	int meio;
	int fim = boids.size();
	while(fim >= inicio){
		meio = (inicio+fim)/2;
		advance(i, meio-posicao);
		posicao=meio;
		if((*i).id < id){
			inicio = meio +1;
		} else if((*i).id > id){
			fim = meio -1;
		} else {
			break;
		} 
	}
	return &(*i);
}

//adicionar e remover boids

void Boid_container::add_boid(double x, double y, double z){
	Boid b(x,y,z);
	boids.push_back(b);
	Boid::idcont++;
}

void Boid_container::add_boid_rand(){
	Vetor aleatorio((signed short)rand(),(signed short)rand(),(signed short)rand());
	aleatorio.normalizar();
	int tamanho = rand()%(max_height-min_height)+min_height;
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
		
		Vetor aceleracao(0,0,0);
		Vetor altura = (*boid_atual).get_coordenadas();
		Vetor versor_altura = altura;
		versor_altura.normalizar();

		if(min_height-altura.norma() > 0)aceleracao += (min_height-altura.norma())*(min_height-altura.norma())*versor_altura;
		else if(altura.norma() - max_height > 0)aceleracao += (max_height-altura.norma())*versor_altura;

		switch((*boid_atual).vizinhos_vistos){
			case 0: esfera_visao(*boid_atual,7, visiveis);
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
		if(aceleracao.norma() > 1){
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

void Boid_container::esfera_visao(Boid& atual, float multiplicador, list<Boid*> &cubo){
	double distancia;
	for(list<Boid>::iterator i = boids.begin(); i != boids.end();i++){
		if((*i).get_coordenadas() != atual.get_coordenadas()){
			distancia = ((*i).get_coordenadas() - atual.get_coordenadas()).norma();
			if(distancia < Boid::CAMPO_DE_VISAO*multiplicador){
				cubo.push_back(&(*i));
			}
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


//definidor da atmosfera

void Boid_container::define_atmosfera(int bottom, int top){
	min_height = bottom;
	max_height = top;
}


