// pushrelabel.cpp

#include <cassert>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stdlib.h>
#include "grafo.h"

using namespace std;

#define INFINITY 10000000

Grafo g;
int vertice_origem;
int vertice_destino;
queue<int> proximo;	
vector<vertice> vertices;
int capacidade_minima = 0;

int escolhe_vertice_ativo_de_maior_potencial() {
	int de_maior_potencial = -1;
	int index;
	for (int i = 0; i < g.nv; i++)
	
		if (g.vertices[i].excesso>0 && 
			g.vertices[i].ativo && 
			g.vertices[i].potencial>de_maior_potencial) {	
			de_maior_potencial=g.vertices[i].potencial;
			index=i;			
		}
	return index;
}

int busca_arco_uv_com_pv_igual_pu_menos_um(int u) {
	int pu=g.vertices[u].potencial;
	for (int i = 0; i < g.na; i++) {		
		if (g.arestas[i].origem==u+1) {
			int v=g.arestas[i].destino-1;
			if(g.vertices[v].potencial==pu-1 && abs(g.arestas[i].capacidade-g.arestas[i].fluxo>0))
				return i;
		}
	}
	return -1;
}

bool tem_ativo() {
	for (int i = 0; i < g.nv; i++)
		if (g.vertices[i].ativo && g.vertices[i].excesso>0)
			return true;	
	return false;
}

void push(aresta a) {		
	int envio=min(g.vertices[a.origem-1].excesso,g.capacidade_livre(a));
	g.arestas[a.chave-1].fluxo+=envio;
	g.arestas[a.oposta-1].fluxo-=envio;
	g.vertices[a.origem-1].excesso-=envio;
	g.vertices[a.destino-1].excesso+=envio;		
}

void relabel(int u) {
	g.vertices[u].potencial++;	
}

int main(int argc, char *argv[]) {
	
	assert(argc==3);
	vertice_origem=atoi(argv[1]);
	vertice_destino=atoi(argv[2]);
	
	//chrono::system_clock::time_point tempo = chrono::system_clock::now();
	
	g.carrega_grafo(cin);
	
	g.vertices[vertice_origem-1].excesso=INFINITY;
	for (int i = 0; i < g.nv; i++)	
		if (!(i==vertice_origem-1||i==vertice_destino-1))
			g.vertices[i].ativo=true;
	g.vertices[vertice_origem-1].potencial=g.nv;		
		
	for (int i = 0; i < g.na; i++)		
		if (g.arestas[i].origem==vertice_origem)		
			push(g.arestas[i]);

	while (tem_ativo()) {		
		int u = escolhe_vertice_ativo_de_maior_potencial();
		while(g.vertices[u].excesso>0) {	
			int a=busca_arco_uv_com_pv_igual_pu_menos_um(u);
			if(a!=-1)
				push(g.arestas[a]);
			else
				relabel(u);						
		}
	}
	
	int fluxo = g.vertices[vertice_destino-1].excesso;
	
	//g.lista_vertices();
	//g.lista_arestas();

	cout << "fluxo:" << fluxo << endl;
	//cout << "tempo:" << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-tempo).count() << endl;	

	return 0;
}
