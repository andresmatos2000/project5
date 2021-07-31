//
// Created by munch on 7/27/2021.
//

#ifndef PROJECT1_VERTEX_H
#define PROJECT1_VERTEX_H
class Vertex{
private:
    int ID;
    bool marked;
    bool recursive = false;
public:
    std::set<int> adjacencyList;
    Vertex(int i){
        ID = i;
        marked = false;
    }
    Vertex(Rule* rule){

    }
    void addAdjacency(int i);
    void mark();
    void unMark();
    bool isMarked();
    void clearList();
    std::set<int> getAdjacencyList();
    int getID();
    void setRecursive();
    bool getRecursive();
};
bool Vertex::getRecursive() {
    return recursive;
}
void Vertex::setRecursive() {
    recursive = true;
}
int Vertex::getID(){
    return ID;
}
void Vertex::clearList(){
    adjacencyList = {};
}
void Vertex::mark(){
    marked = true;
}
void Vertex::unMark(){
    marked = false;
}
bool Vertex::isMarked(){
    return marked;
}
void Vertex::addAdjacency(int i) {
    adjacencyList.insert(i);
}

std::set<int> Vertex::getAdjacencyList() {
    return adjacencyList;
}


#endif //PROJECT1_VERTEX_H
