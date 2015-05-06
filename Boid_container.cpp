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

//construtor
Boid_container::Boid_container(Boid leader){
	lider = leader;
}


//acesso ao campo
Boid& Boid_container::operator[](unsigned int indice){
	list<Boid>::iterator i = boids.begin();
	advance(i, indice);
	return *i;
}


//adicionar e remover boids

void Boid_container::add_boid(double x, double y, double z){
	boids.emplace(boids.end(), x, y, z);
}

void Boid_container::add_boid(int min_dist, int max_dist){
	Vetor aleatorio(rand(),rand(),rand());
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
Vetor Boid_container::altura_pid(Vetor altura){
	static double erro = 0;
	static double acumulador = 0;
	static double altura_anterior = 0;
	static double d_altura = 0;
	erro = altura.norma() - H_SETPOINT;
	acumulador += erro*KI;
	d_altura = altura.norma()-altura_anterior;
	altura_anterior = altura.norma();
	
	Vetor aceleracao = (KP*erro +KD*d_altura + acumulador)*altura;	//se estiver mais alto que o setpoint, aceleracao é positiva
	return aceleracao;
}

void Boid_container::refresh_boids(){
	for(list<Boid>::iterator boid_atual = boids.begin(); boid_atual != boids.end(); boid_atual++){
		list<Boid*> visiveis;
		esfera_visao(*boid_atual,1, visiveis);
		Vetor aceleracao;
		Vetor distancia = (*boid_atual).get_coordenadas();
		aceleracao -= altura_pid((*boid_atual).get_coordenadas());
		
		if(visiveis.empty()){
			esfera_visao(*boid_atual,16, visiveis);
		} else if(visiveis.size() == 1){
			esfera_visao(*boid_atual,4, visiveis);
		}
		
			
		for(list<Boid*>::iterator boid_atuante = visiveis.begin(); boid_atuante != visiveis.end(); boid_atuante++){
			Vetor distancia = (*boid_atuante)->get_coordenadas() - (*boid_atual).get_coordenadas();
			aceleracao += ((K_COESAO/(distancia.norma()/distancia.norma()))*distancia);
			aceleracao -= ((K_REPULSAO/distancia.norma()/distancia.norma()/distancia.norma())*distancia);
			aceleracao += ((K_ALINHAMENTO/distancia.norma()/distancia.norma())*(*boid_atuante)->get_velocidade());
		}
		(*boid_atual).mudar_aceleracao(aceleracao);
		
	}
	
	for(list<Boid>::iterator atual = boids.begin(); atual != boids.end(); ++atual){
		(*atual).refresh();
	}
}




list<Boid*> Boid_container::esfera_visao(Boid& atual, float multiplicador, list<Boid*> &cubo){
	
	double x0 = atual.get_coordenadas().x - Boid::CAMPO_DE_VISAO*multiplicador;
	double x1 = atual.get_coordenadas().x + Boid::CAMPO_DE_VISAO*multiplicador;
	double y0 = atual.get_coordenadas().y - Boid::CAMPO_DE_VISAO*multiplicador;
	double y1 = atual.get_coordenadas().y + Boid::CAMPO_DE_VISAO*multiplicador;
	double z0 = atual.get_coordenadas().z - Boid::CAMPO_DE_VISAO*multiplicador;
	double z1 = atual.get_coordenadas().z + Boid::CAMPO_DE_VISAO*multiplicador;
	
	list<Boid>::iterator iterador;
	list<Boid*>::iterator sub_iterador;
	int inicio, fim, meio;
	
	
	//selecionar um "cubo de visao"
	
	//selecionar no eixo x
	//sort
	boids.sort(sort_x);
	//obter o menor x maior ou igual a x0
	int borda_menor, borda_maior;
	inicio = 0;
	fim = boids.size();
	while(fim >= inicio){
		meio = (inicio + fim)/2;
		if((*this)[meio].get_coordenadas().x < x0){
			inicio = meio + 1;
		} else {
			while(meio >= 0 && (*this)[meio].get_coordenadas().x >= x0){
				meio--;
			}
			borda_menor = meio + 1;
			break;
		}
	}
	//obter maior x menor ou igual a x1
	inicio = 0;
	fim = boids.size();
	while(fim >= inicio){
		meio = (inicio)/2;
		if((*this)[meio].get_coordenadas().x > x1){
			fim = meio - 1;
		} else {
			while(meio < boids.size() && (*this)[meio].get_coordenadas().x <= x1){
				meio++;
			}
			borda_maior = meio - 1;
			break;
		}
	}
	//selecionar os boids dentro do intervalo [x0, x1]
	iterador = boids.begin();
	advance(iterador, borda_menor);
	for(int i = borda_menor;i<=borda_maior;i++){
		if((*iterador).get_coordenadas() != atual.get_coordenadas()){	//eliminando a si mesmo da lista
			cubo.push_back(&(*iterador));
		}
		iterador++;
	}
	
	//selecionar no eixo y
	//sort
	cubo.sort(sort_y);
	//obter maior y menor que y0
	inicio = 0;
	fim = cubo.size();
	while(fim >= inicio){
		meio = (inicio + fim)/2;
		sub_iterador = cubo.begin();
		advance(sub_iterador, meio);
		if((*sub_iterador)->get_coordenadas().y < y0){
			inicio = meio + 1;
		} else {
			while(meio >= 0 && (*sub_iterador)->get_coordenadas().y >= y0){
				meio--;
				sub_iterador--;
			}
			borda_menor = meio + 1;
			break;
		}
	}
	//obter maior y menor ou igual a y1
	inicio = 0;
	fim = cubo.size();
	while(fim >= inicio){
		meio = (inicio)/2;
		sub_iterador = cubo.begin();
		advance(sub_iterador, meio);
		if((*sub_iterador)->get_coordenadas().y > y1){
			fim = meio - 1;
		} else {
			while(meio < boids.size() && (*sub_iterador)->get_coordenadas().y <= y1){
				meio++;
				sub_iterador++;
			}
			borda_maior = meio - 1;
			break;
		}
	}
	//eliminar os boids fora do intervalo [y0, y1]
	if(borda_maior < cubo.size() -1){
		sub_iterador = cubo.begin();
		advance(sub_iterador, borda_maior +1);
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
	inicio = 0;
	fim = cubo.size();
	while(fim >= inicio){
		meio = (inicio + fim)/2;
		sub_iterador = cubo.begin();
		advance(sub_iterador, meio);
		if((*sub_iterador)->get_coordenadas().z < z0){
			inicio = meio + 1;
		} else {
			while(meio >= 0 && (*sub_iterador)->get_coordenadas().z >= z0){
				meio--;
				sub_iterador--;
			}
			borda_menor = meio + 1;
			break;
		}
	}
	//obter maior z menor ou igual a z1
	inicio = 0;
	fim = cubo.size();
	while(fim >= inicio){
		meio = (inicio)/2;
		sub_iterador = cubo.begin();
		advance(sub_iterador, meio);
		if((*sub_iterador)->get_coordenadas().z > z1){
			fim = meio - 1;
		} else {
			while(meio < boids.size() && (*sub_iterador)->get_coordenadas().z <= z1){
				meio++;
				sub_iterador++;
			}
			borda_maior = meio - 1;
			break;
		}
	}
	//eliminar os boids fora do intervalo [z0, z1]
	if(borda_maior < cubo.size() -1){
		sub_iterador = cubo.begin();
		advance(sub_iterador, borda_maior +1);
		cubo.erase(sub_iterador, cubo.end());
	}
	
	if(borda_menor > 0){
		sub_iterador = cubo.begin();
		advance(sub_iterador, borda_menor);
		cubo.erase(cubo.begin(),sub_iterador);
	}
		
	//cubo definido, filtrar para esfera
	sub_iterador = cubo.begin();
	while(sub_iterador != cubo.end()){
		Vetor distancia = (*sub_iterador)->get_coordenadas() - atual.get_coordenadas();
		if(distancia.norma() > Boid::CAMPO_DE_VISAO*multiplicador){
			sub_iterador = cubo.erase(sub_iterador);
		} else {
			sub_iterador++;
		}
	}
	
	return cubo;	//esfera de visão
	
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
		local = (*atual).get_coordenadas();
		glPushMatrix();
		glTranslated(local.x, local.y, local.z);
		(*atual).draw();
		glPopMatrix();
	}
}


