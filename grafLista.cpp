#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

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
    wierzcholki[i_Vertex_Index_2].push_back(i_Vertex_Index_1);

    }
    bool removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2){
        for (int i = 0; i < wierzcholki[i_Vertex_Index_1].size();i++) {
            if (wierzcholki[i_Vertex_Index_1][i] == i_Vertex_Index_2) {
                wierzcholki[i_Vertex_Index_1].erase(wierzcholki[i_Vertex_Index_1].begin() + i);
                return 1;
            }
        }
        if(removeEdge(i_Vertex_Index_2,i_Vertex_Index_1)){
            return 1;
        }
        return 0;
    }
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2){
        for (int i = 0; i < wierzcholki[i_Vertex_Index_1].size();i++) {
            if (wierzcholki[i_Vertex_Index_1][i] == i_Vertex_Index_2) {
                return 1;
            }
        }
        if(checkEdge(i_Vertex_Index_2,i_Vertex_Index_1)){
            return 1;
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

        createVertices(values[0]);

        for (size_t i = 1; i + 1 < values.size(); i += 2) {
            addEdge(values[i], values[i + 1]);
        }
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
