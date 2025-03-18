#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

class Grafo {
private:
    unordered_map<char, vector<char>> listaAdjacencia;

public:
    // Adiciona uma aresta ao grafo
    void adicionarAresta(char no1, char no2) {
        listaAdjacencia[no1].push_back(no2);
        listaAdjacencia[no2].push_back(no1);
    }

    // Remove uma aresta do grafo
    void removerAresta(char no1, char no2) {
        auto &vizinhosNo1 = listaAdjacencia[no1];
        auto &vizinhosNo2 = listaAdjacencia[no2];

        vizinhosNo1.erase(remove(vizinhosNo1.begin(), vizinhosNo1.end(), no2), vizinhosNo1.end());
        vizinhosNo2.erase(remove(vizinhosNo2.begin(), vizinhosNo2.end(), no1), vizinhosNo2.end());
    }

    // Verifica se o grafo ainda est� conectado
    bool ehConexo() {
        if (listaAdjacencia.empty()) return true;

        unordered_map<char, bool> visitado;
        vector<char> pilha;
        char noInicial = listaAdjacencia.begin()->first;
        pilha.push_back(noInicial);
        visitado[noInicial] = true;

        while (!pilha.empty()) {
            char no = pilha.back();
            pilha.pop_back();

            for (char vizinho : listaAdjacencia[no]) {
                if (!visitado[vizinho]) {
                    visitado[vizinho] = true;
                    pilha.push_back(vizinho);
                }
            }
        }

        for (const auto &par : listaAdjacencia) {
            if (!visitado[par.first])
                return false;
        }
        return true;
    }

    // Verifica se uma aresta � uma ponte
    bool ehPonte(char no1, char no2) {
        if (listaAdjacencia[no1].size() == 1) return false; // Se for a �nica aresta, n�o � ponte

        removerAresta(no1, no2); // Remove a aresta para testar

        bool resultado = !ehConexo(); // Se o grafo ficar desconexo, era uma ponte

        adicionarAresta(no1, no2); // Restaura a aresta

        return resultado;
    }

    // Escolhe o v�rtice inicial para o caminho Euleriano
    char encontrarNoInicial() {
        vector<char> verticesImpares;
        for (const auto &par : listaAdjacencia) {
            if (par.second.size() % 2 != 0) {
                verticesImpares.push_back(par.first);
            }
        }

        if (!verticesImpares.empty()) {
            return verticesImpares[0]; // Come�a em um v�rtice de grau �mpar (se houver)
        }

        return listaAdjacencia.begin()->first; // Se n�o houver �mpares, come�a de qualquer lugar
    }

    // Encontra e imprime o caminho Euleriano usando o Algoritmo de Fleury
    void encontrarCaminhoEuleriano() {
        char noInicial = encontrarNoInicial();
        cout << "Caminho Euleriano usando metodo Naive: ";
        encontrarCaminhoEulerianoAux(noInicial);
        cout << endl;
    }

    // Fun��o recursiva para percorrer todas as arestas
    void encontrarCaminhoEulerianoAux(char no) {
        while (!listaAdjacencia[no].empty()) {
            char vizinhoEscolhido = listaAdjacencia[no].front();

            if (listaAdjacencia[no].size() > 1) {
                for (char vizinho : listaAdjacencia[no]) {
                    if (!ehPonte(no, vizinho)) {
                        vizinhoEscolhido = vizinho;
                        break;
                    }
                }
            }

            cout << no << " -> ";
            removerAresta(no, vizinhoEscolhido);
            encontrarCaminhoEulerianoAux(vizinhoEscolhido);
            return;
        }
        cout << no; // �ltimo v�rtice do caminho
    }

    // Testa todas as arestas para identificar pontes (usando naive.cpp)
    void testarTodasArestas() {
        vector<pair<char, char>> arestas;

        for (const auto &par : listaAdjacencia) {
            for (char vizinho : par.second) {
                if (par.first < vizinho) {
                    arestas.emplace_back(par.first, vizinho);
                }
            }
        }

        for (const auto &aresta : arestas) {
            removerAresta(aresta.first, aresta.second);

            if (!ehConexo()) {
                cout << "Aresta (" << aresta.first << "," << aresta.second << ") = ponte" << endl;
            }

            adicionarAresta(aresta.first, aresta.second);
        }
    }
};

int main() {
    Grafo g;

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

    auto inicio = std::chrono::high_resolution_clock::now();

    // Testa todas as arestas antes de rodar o Algoritmo de Fleury
    cout << "Testando todas as arestas para pontes: " << endl;
    g.testarTodasArestas(); // Usa a fun��o do naive.cpp

    // Encontra o caminho Euleriano
    g.encontrarCaminhoEuleriano();

    auto fim = std::chrono::high_resolution_clock::now();

    // Calcula a duração
    std::chrono::duration<double> duracao = fim - inicio;

    // Imprime o tempo decorrido em segundos
    std::cout << "Tempo de execucao: " << duracao.count() << " segundos" << std::endl;

    return 0;
}
