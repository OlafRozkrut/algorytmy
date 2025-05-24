#pragma once
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
    int matrix[100][100] = {0}; 
    int numberOfVertices = 0;

public:
    Graf() {}

    void createVertices(int ile) {
        numberOfVertices = ile;
        for (int i = 0; i < ile; i++) {
            matrix[i][i] = 1; // Znak istnienia wierzchołka
        }
    }

    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2, int waga) {
        if (i_Vertex_Index_1 >= numberOfVertices || i_Vertex_Index_2 >= numberOfVertices) {
            cout << "Nieprawidlowe indeksy wierzcholkow!\n";
            return;
        }
        if (matrix[i_Vertex_Index_1][i_Vertex_Index_1] == 1 &&
            matrix[i_Vertex_Index_2][i_Vertex_Index_2] == 1) {
            matrix[i_Vertex_Index_1][i_Vertex_Index_2] = waga;
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
            cout << "Nie mozna usunac krawedzi (brak krawedzi)\n";
        }
    }

    int checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
        if (i_Vertex_Index_1 >= numberOfVertices || i_Vertex_Index_2 >= numberOfVertices) {
            return -1;
        }
        return matrix[i_Vertex_Index_1][i_Vertex_Index_2];
    }

    int vertexDegree(int idx) {
        if (idx >= numberOfVertices || matrix[idx][idx] == 0) return 0;
        int count = 0;
        for (int i = 0; i < numberOfVertices; i++) {
            if (i != idx && matrix[idx][i] != 0) {
                count++;
            }
        }
        return count;
    }

    vector<int> getNeighbourIndices(int idx) {
        vector<int> neighbours;
        if (idx >= numberOfVertices) return neighbours;

        for (int i = 0; i < numberOfVertices; i++) {
            if (i != idx && matrix[idx][i] != 0) {
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
            for (int j = 0; j < numberOfVertices; j++) {
                if (i != j && matrix[i][j] != 0) {
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

        if (values.size() < 1 || (values.size() - 1) % 3 != 0) {
            cerr << "Nieprawidlowy format pliku!" << endl;
            return;
        }

        createVertices(values[0]);

        for (size_t i = 1; i + 2 < values.size(); i += 3) {
            addEdge(values[i], values[i + 1], values[i + 2]);
        }
    }

    vector<int> dijkstra(int start){
        vector<int> odleglosci(100);//TABLICA D
        vector<int> poprzednicy(100,-1);//tablica p
        vector<int> odwiedzone;
        for(int i=0;i<numberOfVertices;i++){
            /*if(i == start){
                odleglosci[start] = 0;
            }
            else if(matrix[start][i]>0&&matrix[i][i]){
                odleglosci[i] = checkEdge(start,i);
            }
            else{
                odleglosci[i] = -1;
            }*/
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
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                matrix[i][j] = 0;
            }
        }
        numberOfVertices = 0;
    }
};



int main() {
    Graf G;    
    G.readFromFile("grafD1.txt");
    G.printNeighbourIndices(6);
    vector<int> dupa = G.dijkstra(5);
    for(int i=0;i<20;i++){
        cout << i << " = " << dupa[i] << endl;
    }
    return 0;
}
