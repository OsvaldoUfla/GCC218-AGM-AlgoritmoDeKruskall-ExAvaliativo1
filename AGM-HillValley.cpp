#include<utility>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

typedef pair<int, int> ii; // pares de inteiros
typedef vector<int> vi; // vetor de inteiros

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

int main()
{
    // lista de arestas: compostos por uma tripla (peso, (u,v))
    vector<pair<int, ii>> arestas;
    vector<pair<int, ii>> AGM;    //armazena AGM

    int n, m; // numero de vertices e numero de arestas
    cin >> n >> m;
 
    int u, v, w; // extremos das arestas, e peso de cada aresta
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        arestas.push_back(make_pair(w, ii(u, v)));
    }
 
    cout << "Custo da AGM: " << kruskall(arestas, n, m, AGM) << endl;
    
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
    return 0;

}