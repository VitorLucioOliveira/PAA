#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

class Grafo {
private:
    unordered_map<char, vector<char>> listaAdjacencia;
    int tempo;

    void encontrarPontesDFS(char no, char pai, unordered_map<char, bool>& visitado,
                            unordered_map<char, int>& descoberta, unordered_map<char, int>& baixo,
                            vector<pair<char, char>>& pontes) {
        visitado[no] = true;
        descoberta[no] = baixo[no] = ++tempo;

        for (char vizinho : listaAdjacencia[no]) {
            if (vizinho == pai) continue;

            if (!visitado[vizinho]) {
                encontrarPontesDFS(vizinho, no, visitado, descoberta, baixo, pontes);
                baixo[no] = min(baixo[no], baixo[vizinho]);

                if (baixo[vizinho] > descoberta[no]) {
                    pontes.push_back({no, vizinho});
                }
            } else {
                baixo[no] = min(baixo[no], descoberta[vizinho]);
            }
        }
    }

public:
    void adicionarAresta(char no1, char no2) {
        listaAdjacencia[no1].push_back(no2);
        listaAdjacencia[no2].push_back(no1);
    }

    void removerAresta(char no1, char no2) {
        listaAdjacencia[no1].erase(remove(listaAdjacencia[no1].begin(), listaAdjacencia[no1].end(), no2), listaAdjacencia[no1].end());
        listaAdjacencia[no2].erase(remove(listaAdjacencia[no2].begin(), listaAdjacencia[no2].end(), no1), listaAdjacencia[no2].end());
    }

    vector<pair<char, char>> encontrarPontes() {
        tempo = 0;
        unordered_map<char, bool> visitado;
        unordered_map<char, int> descoberta;
        unordered_map<char, int> baixo;
        vector<pair<char, char>> pontes;

        for (const auto& par : listaAdjacencia) {
            if (!visitado[par.first]) {
                encontrarPontesDFS(par.first, ' ', visitado, descoberta, baixo, pontes);
            }
        }
        return pontes;
    }

    bool ehPonte(char no1, char no2) {
        removerAresta(no1, no2);

        unordered_map<char, bool> visitado;
        dfs(no1, visitado);

        bool desconectado = (visitado.size() != listaAdjacencia.size());

        adicionarAresta(no1, no2);

        return desconectado;
    }

    void dfs(char no, unordered_map<char, bool>& visitado) {
        visitado[no] = true;
        for (char vizinho : listaAdjacencia[no]) {
            if (!visitado[vizinho]) {
                dfs(vizinho, visitado);
            }
        }
    }

    char encontrarNoInicial() {
        for (const auto& par : listaAdjacencia) {
            if (par.second.size() % 2 != 0) {
                return par.first;
            }
        }
        return listaAdjacencia.begin()->first;
    }

    void encontrarCaminhoEuleriano() {
        char noInicial = encontrarNoInicial();
        cout << "Caminho Euleriano usando Tarjan: ";
        encontrarCaminhoEulerianoAux(noInicial);
        cout << endl;
    }

    void encontrarCaminhoEulerianoAux(char no) {
        while (!listaAdjacencia[no].empty()) {
            char vizinhoEscolhido = listaAdjacencia[no].front();
            bool encontrouNaoPonte = false;

            for (char vizinho : listaAdjacencia[no]) {
                if (!ehPonte(no, vizinho)) {
                    vizinhoEscolhido = vizinho;
                    encontrouNaoPonte = true;
                    break;
                }
            }

            if (!encontrouNaoPonte) {
                vizinhoEscolhido = listaAdjacencia[no].front();
            }

            cout << no << " -> ";
            removerAresta(no, vizinhoEscolhido);
            no = vizinhoEscolhido;
        }
        cout << no; // �ltimo v�rtice do caminho
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
    g.encontrarCaminhoEuleriano();

    auto fim = std::chrono::high_resolution_clock::now();

    // Calcula a duração
    std::chrono::duration<double> duracao = fim - inicio;

    // Imprime o tempo decorrido em segundos
    std::cout << "Tempo de execucao: " << duracao.count() << " segundos" << std::endl;


    return 0;
}