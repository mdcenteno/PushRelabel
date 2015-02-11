// grafo.cpp

#include <string>
#include <iostream>
#include <sstream> 
#include <fstream> 
#include <vector>
#include <stdlib.h>
#include "grafo.h"

using namespace std;

Grafo::Grafo() {
}
Grafo::~Grafo() {
}
void Grafo::lista_vertices() {
	printf("vertices: \n");
	for (int i = 0; i < nv; i++)	
		printf("c%d a%d e%d p%d;\n", vertices[i].chave, vertices[i].ativo, vertices[i].excesso, vertices[i].potencial);
	//printf("\n");
}
void Grafo::lista_arestas() {
	printf("arestas: \n");
	for (int i = 0; i < na; i++)	
		printf("c%d o%d d%d op%d cap%d f%d \n", arestas[i].chave, arestas[i].origem, arestas[i].destino, arestas[i].oposta, arestas[i].capacidade, arestas[i].fluxo);
	//printf("\n");
}
vertice Grafo::cria_vertice(int c) {
	vertice v;
	v.chave=c;
	v.ativo=0;
	v.excesso=0;
	v.potencial=0;
	return v;
}
aresta Grafo::cria_aresta(int c, int o, int d, int cap, int op) {
	aresta a;
	a.chave=c;
	a.origem=o;
	a.destino = d;
	a.oposta=op;
	a.capacidade = cap;
	a.fluxo=0;
	return a;
}
int Grafo::capacidade_livre(aresta a) {
	return a.capacidade-a.fluxo;
}

void Grafo::read_dimacs(std::istream& in) {
	string line="", dummy;
	while (line.substr(0,5) != "p max")
		getline(in,line);		

	// (1) get nodes and edges
	std::stringstream linestr;
 
	linestr.str(line);
	linestr >> dummy >> dummy >> nv >> na;
	
	//cout << nv << " " << na << endl;
	
	for (int i = 0; i < nv; i++) {
		//vertice vert = cria_vertice(i+1);	
		//vertices.push_back(vert);
		vertices.push_back(cria_vertice(i+1));
	}
	
	int i=0;
	while(i<na) {
		getline(in,line);
		//cout << line << endl;
		if (line.substr(0,2) == "a ") {
			std::stringstream arc(line);
			unsigned u,v,c;
			char ac;
			arc >> ac >> u >> v >> c;
			// processar arco (u,v) com capacidade c			
			arestas.push_back(cria_aresta(i+1,u,v,c,0));
			i++;
		}
	}
}
void Grafo::trata_opostas_existentes(int i, int j) {	
	cout << "olá!" << endl;
	arestas[i].oposta=arestas[j].chave;
	arestas[j].oposta=arestas[i].chave;
}
void Grafo::acrescenta_opostas(){	
	int nova_chave = na;
	for (int i = 0; i < na; i++) {
		bool existe_oposta = false;

		if(arestas[i].oposta==0) {
			for (int j = i+1; j < na; j++) {					
				if (arestas[i].origem==arestas[j].destino && 
					arestas[i].destino==arestas[j].origem) {
					existe_oposta = true;
					
					//cout << "i" << i << arestas[i].origem << " " << arestas[i].destino << " " << arestas[i].oposta << endl;
					//cout << "j" << j << arestas[j].origem << " " << arestas[j].destino << " " << arestas[j].oposta << endl;					
					//lista_arestas();
					
					trata_opostas_existentes(i,j);
					
					//lista_arestas();					
					//cout << "i" << i << arestas[i].origem << " " << arestas[i].destino << " " << arestas[i].oposta << endl;
					//cout << "j" << j << arestas[j].origem << " " << arestas[j].destino << " " << arestas[j].oposta << endl;
					
					break;
				}
			}
		}
		else {
			existe_oposta = true;
		}
				
		if (!existe_oposta) {
			nova_chave++;
			arestas.push_back(cria_aresta(nova_chave,arestas[i].destino,arestas[i].origem,0,arestas[i].chave));
			arestas[i].oposta=nova_chave;			
		}
	}
	na=nova_chave;
}
void Grafo::carrega_grafo(istream& is) {
	read_dimacs(is);
	//lista_arestas();
	acrescenta_opostas();	
}
