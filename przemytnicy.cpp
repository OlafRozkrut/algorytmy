#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1e9; // 1 000 000 000

class Graf {
    vector<vector<int>> matrix;
    int numberOfVertices = 0;
    

public:
    Graf() {}
    vector<int> ceny;

    void createVertices(int ile) {
        numberOfVertices = ile;
        matrix.assign(ile, vector<int>(ile, 0));
        for (int i = 0; i < ile; i++) {
            matrix[i][i] = 1;
        }
    }

    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2, int wartosc) {
        if (i_Vertex_Index_1 >= numberOfVertices || i_Vertex_Index_2 >= numberOfVertices) {
            cout << "Nieprawidlowe indeksy wierzcholkow!\n";
            return;
        }
        if (matrix[i_Vertex_Index_1][i_Vertex_Index_1] > 0 &&
            matrix[i_Vertex_Index_2][i_Vertex_Index_2] > 0) {
            matrix[i_Vertex_Index_1][i_Vertex_Index_2] = wartosc;
        } else {
            cout << "Nie mozna utworzyc krawedzi\n";
        }
    }

    void removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
        if (i_Vertex_Index_1 >= numberOfVertices || i_Vertex_Index_2 >= numberOfVertices) {
            cout << "Nieprawidlowe indeksy wierzcholkow!\n";
            return;
        }
        if (matrix[i_Vertex_Index_1][i_Vertex_Index_2] != 0) {
            matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 0;
        } else {
            cout << "Nie mozna usunac krawedzi\n";
        }
    }

    int checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
        if (i_Vertex_Index_1 >= numberOfVertices || i_Vertex_Index_2 >= numberOfVertices) {
            return 0;
        }
        return matrix[i_Vertex_Index_1][i_Vertex_Index_2];
    }

    int vertexDegree(int idx) {
        if (idx >= numberOfVertices || matrix[idx][idx] == 0) return 0;

        int count = 0;
        for (int i = 0; i < numberOfVertices; i++) {
            if (matrix[idx][i]) {
                count++;
            }
        }
        return count - 1;
    }

    vector<int> getNeighbourIndices(int idx) {
        vector<int> neighbours;
        if (idx >= numberOfVertices) return neighbours;

        for (int i = 0; i < numberOfVertices; i++) {
            if (matrix[idx][i] && i != idx) {
                neighbours.push_back(i);
            }
        }
        return neighbours;
    }

    void printNeighbourIndices(int idx) {
        vector<int> neighbours = getNeighbourIndices(idx);
        for (int num : neighbours) {
            cout << num << " ";
        }
        cout << endl;
    }

    int getNumberOfEdges() {
        int count = 0;
        for (int i = 0; i < numberOfVertices; i++) {
            for (int j = i + 1; j < numberOfVertices; j++) {
                if (matrix[i][j] != 0) {
                    count++;
                }
            }
        }
        return count;
    }

    void readFromFile(string path) {
        ifstream file(path);
        if (!file) {
            cerr << "Blad otwierania pliku!" << endl;
            return;
        }

        vector<int> values;
        int value;
        while (file >> value) {
            values.push_back(value);
        }
        file.close();

        if (values.empty()) {
            cerr << "Plik jest pusty!" << endl;
            return;
        }

        int n = values[0];
        createVertices(n);

        vector<int> prices(n + 1);  // ceny od indeksu 1 do n
        

        for (int i = 1; i <= n; i++) {
            ceny[i] = values[i];
        }
        
        int m = values[n + 1];

        for (int i = n + 2; i < values.size(); i += 3) {
            addEdge(values[i]-1, values[i + 1]-1, values[i + 2]);
        }
    }

    vector<int> dijkstra(int start){
        vector<int> odleglosci(numberOfVertices, INF);
        vector<int> poprzednicy(numberOfVertices, -1);
        vector<int> odwiedzone;
        for(int i=0;i<numberOfVertices;i++){

           odleglosci[i] = INF;

        }
        odleglosci[start]=0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});
        int teraz_sprawdzane;
        while (!pq.empty()){
            teraz_sprawdzane = pq.top().second;
            pq.pop();
            if(find(odwiedzone.begin(), odwiedzone.end(), teraz_sprawdzane) != odwiedzone.end()) {
                continue;
            }
            vector<int> sasiedzi = getNeighbourIndices(teraz_sprawdzane);
            for(int i=0;i<sasiedzi.size();i++){
                if(odleglosci[teraz_sprawdzane]+matrix[teraz_sprawdzane][sasiedzi[i]]<odleglosci[sasiedzi[i]]){
                    odleglosci[sasiedzi[i]] = odleglosci[teraz_sprawdzane]+matrix[teraz_sprawdzane][sasiedzi[i]];
                    poprzednicy[sasiedzi[i]] = teraz_sprawdzane;
                    pq.push({odleglosci[sasiedzi[i]],sasiedzi[i]});
                }
                
            }
            odwiedzone.push_back(teraz_sprawdzane);
        }
        return odleglosci;
    }

private:
    void clear() {
        matrix.clear();
        numberOfVertices = 0;
    }
};

int main() {
    Graf* G = new Graf(); 
    G->readFromFile("dane.txt");
    
    auto it = min_element(G->ceny.begin()+1, G->ceny.end());
    int najmniejsza_cena = distance(G->ceny.begin(), it);

    vector<int> sciezka_od_zlota = G->dijkstra(0);
    vector<int> sciezka_do_zlota = G->dijkstra(najmniejsza_cena);
    int cena_koncowa = sciezka_od_zlota[najmniejsza_cena] + sciezka_do_zlota[0] + G->ceny[najmniejsza_cena]/2;
    cout << cena_koncowa << endl;

    return 0;
}
