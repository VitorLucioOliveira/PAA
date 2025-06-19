#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class Grafo
{
private:
    unordered_map<char, vector<char>> listaAdjacencia;

public:
    void adicionarAresta(char no1, char no2)
    {
        listaAdjacencia[no1].push_back(no2);
        listaAdjacencia[no2].push_back(no1);
    }

    void removerAresta(char no1, char no2)
    {
        auto &vizinhosNo1 = listaAdjacencia[no1];
        auto &vizinhosNo2 = listaAdjacencia[no2];

        vizinhosNo1.erase(remove(vizinhosNo1.begin(), vizinhosNo1.end(), no2), vizinhosNo1.end());
        vizinhosNo2.erase(remove(vizinhosNo2.begin(), vizinhosNo2.end(), no1), vizinhosNo2.end());
    }

    bool ehConexo()
    {
        if (listaAdjacencia.empty()){ return true;} // se o grafo é nulo, uma interpretação é que este é conexo

        unordered_map<char, bool> visitado;
        queue<char> fila;
        char noInicial = listaAdjacencia.begin()->first;
        fila.push(noInicial);
        visitado[noInicial] = true;

        while (!fila.empty())
        {
            char no = fila.front();
            fila.pop();

            for (char vizinho : listaAdjacencia[no])
            {
                if (!visitado[vizinho])
                {
                    visitado[vizinho] = true;
                    fila.push(vizinho);
                }
            }
        }

        for (const auto &par : listaAdjacencia)
        {
            if (!visitado[par.first])
                return false;
        }
        return true;
    }

    void testarTodasArestas()
    {
        vector<pair<char, char>> arestas; // vetor de arestas para armazenar todas as arestas do grafo

        for (const auto &par : listaAdjacencia) // para cada nó do grafo, adicionamos todas as arestas que saem dele
        {
            for (char vizinho : par.second)
            {
                if (par.first < vizinho) // evita adicionar arestas duplicadas
                {
                    arestas.emplace_back(par.first, vizinho);
                }
            }
        }

        for (const auto &aresta : arestas) // para cada aresta do grafo, testamos se ela é uma ponte
        {
            removerAresta(aresta.first, aresta.second);

            if (!ehConexo())
            {
                cout << "Aresta (" << aresta.first << "," << aresta.second << ") = ponte" << endl;
            }

            adicionarAresta(aresta.first, aresta.second); 
            // como removemos a aresta logo acima, essa linha garante que na proxima iteração o grafo volte a sua forma original,
            // evitando que arestas retiradas anteriormente continuem fora do grafo, o que iria deixar a nossa resposta imprecísa.
        }
    }
};

int main()
{
    Grafo g;
    // teste com o grafo mostrado no documento .pdf da atividade1
    g.adicionarAresta('A', 'B');
    g.adicionarAresta('A', 'E');
    g.adicionarAresta('A', 'D');
    g.adicionarAresta('B', 'C');
    g.adicionarAresta('B', 'D');
    g.adicionarAresta('B', 'E');
    g.adicionarAresta('C', 'D');
    g.adicionarAresta('C', 'E');
    g.adicionarAresta('C', 'F');
    g.adicionarAresta('D', 'F');
    g.adicionarAresta('E', 'F');
    g.adicionarAresta('F', 'G');
    g.adicionarAresta('G', 'I');
    g.adicionarAresta('G', 'H');
    g.adicionarAresta('H', 'I');

    g.testarTodasArestas();
    return 0;
}