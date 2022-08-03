#include<utility>
#include<vector>
#include<iostream>
#include <queue>
#include<algorithm>
#include <functional>

using namespace std;

typedef pair<int, int> ii; // pares de inteiros
typedef vector<int> vi; // vetor de inteiros

#define NAO_VISITADO 0

// Raiz da DFS
int raiz;

// Armazena a informacao se um vertice eh de articulacao
bool* articulacoes;

/*
 * Parametros:
 *  u -> vertice a ser explorado
 *  lista_adj -> lista de adjacencia, que modela o grafo
 *  low -> vetor com os menores tempos de descoberta de arestas que abracam um vertice
 *  d -> vetor dos tempos de descoberta pre-ordem de todos os vertices
 *  pai -> vetor com os pais de todos os vertices
 *  cont_dfs -> contador do tempo de descoberta em profundidade dos vertices
 *  filhos_raiz -> conta quantos filhos a raiz possui na DFS
 */
void tarjan(int u, vector<int>* lista_adj, int* low, int* d, int* pai, int& cont_dfs, int& filhos_raiz)
{
    low[u] = d[u] = cont_dfs++;
 
    for(auto it = lista_adj[u].begin(); it != lista_adj[u].end(); it++)
    {
        int v = *it;
        if(d[v] == NAO_VISITADO)
        {
            pai[v] = u;
     
            if(u == raiz)
            {
                filhos_raiz++;
            }
        
            tarjan(v, lista_adj, low, d, pai, cont_dfs, filhos_raiz);
        
            if(low[v] >= d[u])
            {
                articulacoes[u] = true;
            }
        
            if(low[v] > d[u])
            {
                //cout << "ponte: (" << u << ", " << v << ")" << endl;
            }
     
            low[u] = min(low[u], low[v]);
        }
     
        // Nao eh um ciclo trivial
        else if(v != pai[u])
        {
            low[u] = min(low[u], low[v]);
        }
    }
}

class UFDS
{
    public:
      // construtor com parametro: n eh o numero de conjuntos disjuntos
      UFDS(int n)
      {
          rank.assign(n, 0);
          p.assign(n, 0);
          for(int i = 0; i < n; i++)
            p[i] = i;
      }
 
      /* Dado um elemento do conjunto, busca-se seu pai no conjunto disjunto e o 
       * atualiza (se necessário) para o ancestral de maior nivel na arvore.
       *
       * Parametros
       * i: identificacao do elemento cujo o conjunto sera buscado.
       */
      int busca(int i)
      {
          if(p[i] == i)
              return i;
      
          p[i] = busca(p[i]);
          return p[i];
      }
 
      /* Dado dois elementos do conjunto, verifica-se se esses elementos possuem o
      * o mesmo pai na floresta disjunta.
      *
      * Parametros
      * i: um elemento qualquer.
      * j: um elemento qualquer.
      */
      bool mesmoConjunto(int i, int j)
      {
          return busca(i) == busca(j);
      }
 
      /* Dados dois elementos, une os seus respectivos conjuntos considerando o rank 
      * de maior valor (em caso de empate, o elemento de maio indice)
      *
      * Parametros
      * i: um elemento qualquer.
      * j: um elemento qualquer.
      */
      void uniao(int i, int j)
      {
          if(!mesmoConjunto(i, j))
          {
              int c1 = busca(i);
              int c2 = busca(j);
          
              if(rank[c1] > rank[c2])
                  p[c2] = c1;
          
              else
              {
                  p[c1] = c2;
                  if(rank[c1] == rank[c2])
                      rank[c2]++;
              }
          }
      }
 
      /* Imprime as informacoes de quais os elementos estao em cada conjunto.
      * Apresenta-se tambem o rank de cada elemento
      *
      * Parametros
      * p: vetor que armazena os pais de cada vertice no conjunto disjunto.
      * rank: vetor que armazena o rank de cada elemento do conjunto.
      * n: numero de elementos no conjunto
      */
      friend ostream &operator<<(ostream& saida, const UFDS& conjunto)
      {
          for(int i = 0; i < conjunto.p.size(); i++)
            saida << i << ": p(" << conjunto.p[i] << "), rank(" << conjunto.rank[i] << ")";
          return saida;
      }
 
    private:
      // vetor que armazena os pais de cada vertice no conjunto disjunto
      vi p;
 
      // vetor que armazena o rank de cada elemento do conjunto
      vi rank;
};

/* retorna o custo da AGM
 * Parametros:
 *  arestas: lista da arestas
 *  n: quantidade de vertices
 *  m: quantidade de arestas
 */
int kruskall(vector<pair<int, ii>>& arestas, int n, int m, vector<pair<int, ii>>& AGM)
{
    // ordenacao em O(mlogm), de acordo com https://www.cplusplus.com/reference/algorithm/sort/?kw=sort
    sort(arestas.begin(), arestas.end());
 
    // custo da AGM
    int resultado = 0;
 
    UFDS ufds(n); // codigo equivalente ao MAKE-SET(v) do pseudocodigo
 
    int u, v;
    pair<int, ii> e;
    
    int numero_arestas = 0;
    for(int i = 0; i < m; i++)
    {
        e = arestas[i];
        u = e.second.first;
        v = e.second.second;
        if(!ufds.mesmoConjunto(u, v))
        {
            resultado += e.first;
            AGM.push_back(e);
            numero_arestas++;
            if(numero_arestas == n-1)
              break;
         
            ufds.uniao(u, v);
        }
    }

    return resultado;
}
/*
*Verifica se duas tuplas tem o mesmo conteudo
*retorna true ou false
*/
bool comparaTupla(pair<int, ii> a, pair<int, ii> b)
{
    if(a.first == b.first and
       a.second.first == b.second.first and
       a.second.second == b.second.second)
    {
        return true;
    }
    return false;
}

/*
Busca e Retorna o custo de uma aresta
parametros vetor e tuplas e dois vertices origem e destinos da aresta 
*/
int getCusto(vector<pair<int, ii>>& arestas, int a, int b)
{
    for(auto it = arestas.begin(); it != arestas.end(); it++)
    {
        pair<int, ii> e = *it;
        if( (e.second.first == a and e.second.second == b) 
                                or
             (e.second.first == b and e.second.second == a))
        {
            return e.first;
        }
    }
    return -1;
}

int main()
{
    // lista de arestas: compostos por uma tripla (peso, (u,v))
    vector<pair<int, ii>> arestas;
    vector<pair<int, ii>> AGM;    //armazena AGM

    int custoDaAGM = 0; //armazena o custo da AGM
    int menorAresta = 0; ///Armazena a menor aresta do ciclo 
    int n, m; // numero de vertices e numero de arestas
    cin >> n >> m;
 
    int u, v, w; // extremos das arestas, e peso de cada aresta
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        arestas.push_back(make_pair(w, ii(u, v)));
    }
 
    custoDaAGM = kruskall(arestas, n, m, AGM);
    cout << custoDaAGM  << endl;
    
    for(int i=0; i< arestas.size();i++)
    {
        for(int j=0 ; j< AGM.size(); j++)
        {
            if(comparaTupla(arestas[i], AGM[j]))
            {
                arestas.erase(arestas.begin() + i);
            }
        }
    }

    m= AGM.size();

    // alocando as estruturas auxiliares
    int* low = new int[n+1];
    int* d = new int[n+1];
    int* pai = new int[n+1];
    int cont_dfs = 1;
    int filhos_raiz = 0;
   
    articulacoes = new bool[n+1];
   
    // iniciando as estruturas auxiliares
    for(int i = 1; i <= n; i++)
    {
        low[i] = NAO_VISITADO;
        d[i] = NAO_VISITADO;
        pai[i] = -1;
        articulacoes[i] = false;
    }
   
    vector<int>* lista_adj = new vector<int>[n+1];

    // leitura do grafo
    int x, y, z;
    for(int i = 0; i < m; i++)
    {
        x = AGM[i].second.first ;// lendo as arestas do grafo
        y = AGM[i].second.second;

      // evitando a leitura de vertices repetidos nas listas
      if(find(lista_adj[x].begin(), lista_adj[x].end(), y) != lista_adj[x].end())
      {
        continue;
      }

      // grafo nao-orientado
      lista_adj[x].push_back(y); //x -> y
      lista_adj[y].push_back(x); //x -> y
    }

    x = arestas[0].second.first ;// Copia a aresta de menor valor que não foi usado na AGM 
    y = arestas[0].second.second;
    z = arestas[0].first;


    // adicionando a aresta de menor valor que não foi usado na AGM criando um ciclo
    lista_adj[x].push_back(y); //x -> y
    lista_adj[y].push_back(x); //x -> y
    custoDaAGM = custoDaAGM + z; // Soma no custo da AMG o valor da aresta de menor valor que não foi usado na AGM 

    for(int i = 1; i <= n; i++)
    {
        if(d[i] == NAO_VISITADO)
        {
            raiz = i;
            filhos_raiz = 0;
            tarjan(i,  lista_adj, low, d, pai, cont_dfs, filhos_raiz);
            // Caso especial para vertice de articulacao: a raiz da DFS com mais de 1 filho
            articulacoes[i] = (filhos_raiz > 1);
        }
    }
   
    for(int i = 1; i <= n; i++)
    {
        if(articulacoes[i])
        {
            //cout << "vertice de articulacao: " << i << endl;
        }
    }

    //cout << getCusto(arestas, 3,2) << endl;

    int temp = x;
    while(y != temp)
    {
        x = y;
        y = pai[y];
        if(getCusto(AGM,x, y) > menorAresta)
        {
            menorAresta = getCusto(AGM,x, y);
        }
    }

    cout << custoDaAGM - menorAresta  << endl;

   
    delete[] pai;
    delete[] d;
    delete[] low;
    delete[] articulacoes;
    
    return 0;

}