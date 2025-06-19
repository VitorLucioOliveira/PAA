#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Grafo {
private:
 unordered_map<char, vector<char>> listaAdjacencia;
 int tempo;  // Contador global para o registro da ordem em que os nós serão vizitados

 void encontrarPontesDFS(char no, unordered_map<char, bool>& visitado, 
                        unordered_map<char, int>& descoberta, 
                        unordered_map<char, int>& baixo, 
                        char pai) {
     visitado[no] = true;
     descoberta[no] = baixo[no] = ++tempo;

     for (char vizinho : listaAdjacencia[no]) {
         if (vizinho == pai) continue;

         if (!visitado[vizinho]) {
             encontrarPontesDFS(vizinho, visitado, descoberta, baixo, no);

             baixo[no] = min(baixo[no], baixo[vizinho]);

             if (baixo[vizinho] > descoberta[no]) {    // Caso não haja um caminho alternativo, é ponte
                 cout << "Aresta (" << vizinho << "," << no << ") = ponte" << endl;
             }
         } else {
             baixo[no] = min(baixo[no], descoberta[vizinho]);
         }
     }
 }

public:
 void adicionarAresta(char no1, char no2) {  // Adiciona aresta não direcionada ao grafo
     listaAdjacencia[no1].push_back(no2);
     listaAdjacencia[no2].push_back(no1);
 }

 void encontrarPontes() {  
     unordered_map<char, bool> visitado;
     unordered_map<char, int> descoberta;
     unordered_map<char, int> baixo;
     tempo = 0;

     for (const auto& par : listaAdjacencia) {  // Marca todos os nós como não visitados
         visitado[par.first] = false;
     }

     for (const auto& par : listaAdjacencia) {   // Inicia DFS para todos os componentes não visitados
         if (!visitado[par.first]) {
             encontrarPontesDFS(par.first, visitado, descoberta, baixo, ' ');
         }
     }
 }
};

int main() {
 Grafo g;
 
 // teste com o grafo mostrado no documento .pdf da atividade1
 g.adicionarAresta('A','B');
 g.adicionarAresta('A','E');
 g.adicionarAresta('A','D');
 g.adicionarAresta('B','C');
 g.adicionarAresta('B','D');
 g.adicionarAresta('B','E');
 g.adicionarAresta('C','D');
 g.adicionarAresta('C','E');
 g.adicionarAresta('C','F');
 g.adicionarAresta('D','F');
 g.adicionarAresta('E','F');
 g.adicionarAresta('F','G');
 g.adicionarAresta('G','I');
 g.adicionarAresta('G','H');
 g.adicionarAresta('H','I');

 g.encontrarPontes();
 
 return 0;
}