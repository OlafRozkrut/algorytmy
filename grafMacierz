#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


class Graf {
    int matrix[100][100] = {0}; 
    int numberOfVertices = 0;

public:
    Graf() { numberOfVertices = 0; }

    void createVertices(int ile) {
        numberOfVertices = ile;
        for (int i = 0; i < ile; i++) {
            matrix[i][i] = 1;
        }
    }

    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
        if (i_Vertex_Index_1 >= numberOfVertices || i_Vertex_Index_2 >= numberOfVertices) {
            cout << "Nieprawidlowe indeksy wierzcholkow!\n";
            return;
        }
        if (matrix[i_Vertex_Index_1][i_Vertex_Index_1] == 1 &&
            matrix[i_Vertex_Index_2][i_Vertex_Index_2] == 1) {
            matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 1;
            matrix[i_Vertex_Index_2][i_Vertex_Index_1] = 1;
        } else {
            cout << "Nie mozna utworzyc krawedzi\n";
        }
    }

    void removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
        if (i_Vertex_Index_1 >= numberOfVertices || i_Vertex_Index_2 >= numberOfVertices) {
            cout << "Nieprawidlowe indeksy wierzcholkow!\n";
            return;
        }
        if (matrix[i_Vertex_Index_1][i_Vertex_Index_2] == 1) {
            matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 0;
            matrix[i_Vertex_Index_2][i_Vertex_Index_1] = 0;
        } else {
            cout << "Nie mozna usunac krawedzi\n";
        }
    }

    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
        if (i_Vertex_Index_1 >= numberOfVertices || i_Vertex_Index_2 >= numberOfVertices) {
            return false;
        }
        return matrix[i_Vertex_Index_1][i_Vertex_Index_2] == 1;
    }

    int vertexDegree(int idx) {
        if (idx >= numberOfVertices || matrix[idx][idx] == 0) return 0;

        int count = 0;
        for (int i = 0; i < numberOfVertices; i++) {
            if (matrix[idx][i]) {
                count++;
            }
        }
        return count-1;
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
                if (matrix[i][j] == 1) {
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

        createVertices(values[0]);

        for (size_t i = 1; i + 1 < values.size(); i += 2) {
            addEdge(values[i], values[i + 1]);
        }
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

int main(){

    Graf* G = new Graf();    
    G->createVertices(10);
    G->addEdge(1, 2);
    G->addEdge(2, 3);
    G->addEdge(1, 5);
    std::cout << G->vertexDegree(1)<<"\n";
    std::cout << G->vertexDegree(8) << "\n";
    G->printNeighbourIndices(1);
    G->printNeighbourIndices(1);
    std::cout << G->checkEdge(1, 2)<<"\n";
    G->removeEdge(1, 2);
    G->printNeighbourIndices(1);
    std::cout << G->checkEdge(1, 2) << "\n\n\n\n\n";  
    return 0;
}
