#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stack>

using namespace std;


class Graf
{
    vector<vector<int>> wierzcholki;


public:
    Graf() = default;
    void createVertices(int ile){
        for(int i=0;i<ile;i++){
            vector<int> temp;
            wierzcholki.push_back(temp);
        }
    }    
    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2){
        if (i_Vertex_Index_1 < 0 || i_Vertex_Index_1 >= wierzcholki.size() ||i_Vertex_Index_2 < 0 || i_Vertex_Index_2 >= wierzcholki.size()){
        cerr << "Nieprawidlowy indeks wierzcholka!\n";
        return;
        }

    wierzcholki[i_Vertex_Index_1].push_back(i_Vertex_Index_2);

    }
    bool removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2){
        for (int i = 0; i < wierzcholki[i_Vertex_Index_1].size();i++) {
            if (wierzcholki[i_Vertex_Index_1][i] == i_Vertex_Index_2) {
                wierzcholki[i_Vertex_Index_1].erase(wierzcholki[i_Vertex_Index_1].begin() + i);
                return 1;
            }
        }
        return 0;
    }
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2){
        for (int i = 0; i < wierzcholki[i_Vertex_Index_1].size();i++) {
            if (wierzcholki[i_Vertex_Index_1][i] == i_Vertex_Index_2) {
                return 1;
            }
        }
        return 0;
    }
    int vertexDegree(int idx){
        return wierzcholki[idx].size();
    }
    std::vector<int> getNeighbourIndices(int idx){
        vector<int> temp;
        for(int i=0;i<wierzcholki[idx].size();i++){
            temp.push_back(wierzcholki[idx][i]);
        }
        return temp;
    }
    void printNeighbourIndices(int idx){
        for(int i=0;i<wierzcholki[idx].size();i++){
            cout <<wierzcholki[idx][i] << " ";
        }
        cout << endl;
    }
    int getNumberOfEdges(){
        int ile = 0;
        for(int i=0;i<wierzcholki.size();i++){
            ile += wierzcholki[i].size();
        }
        return ile;
    }
    void readFromFile(std::string path){
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

        for (int i = 0; i < n; ++i) {
            int skarbonka_z_kluczem = values[i + 1] - 1; 
            int skarbonka_docelowa = i;                 
            addEdge(skarbonka_z_kluczem, skarbonka_docelowa);
        }
    }
    

    int countCycles() {
        int n = wierzcholki.size();
        vector<int> visited(n, 0);
        int cycles = 0;

        for (int i = 0; i < n; ++i) {
            if (visited[i] == 0) {
                if (dfsCycle(i, visited)) {
                    cycles++;
                }
            }
        }

        return cycles;
    }
    bool dfsCycle(int v, vector<int>& visited) {
        visited[v] = 1;

        for (int sasiad : wierzcholki[v]) {
            if (visited[sasiad] == 0) {
                if (dfsCycle(sasiad, visited)) return true;
            } else if (visited[sasiad] == 1) {
                return true;
            }
        }

        visited[v] = 2; 
        return false;
    }
    
};



int main(){

    Graf G;
    G.readFromFile("test2.txt");
    int ile = G.countCycles();
    cout << "Minimalna liczba skarbonek: " << ile << endl;


    return 0;
}