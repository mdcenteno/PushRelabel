
struct vertice {
    int chave;
    int ativo;
    int excesso;
    int potencial;
};
struct aresta {
	int chave;	
	int origem;
    int destino;
    int oposta;
    int capacidade;
    int fluxo;
};
class Grafo {
public:  
	int nv;
	int na;
	std::vector<vertice> vertices;
	std::vector<aresta> arestas;		
	
	Grafo();
	~Grafo();	
	void lista_arestas();
	void lista_vertices();
	int capacidade_livre(aresta);
	void carrega_grafo(std::istream&);
private:	
	vertice cria_vertice(int);
	aresta cria_aresta(int,int,int,int,int);
	void read_dimacs(std::istream&);
	void acrescenta_opostas();
	void trata_opostas_existentes(int,int);
};
