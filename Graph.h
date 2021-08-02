//
// Created by munch on 7/26/2021.
//

#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H

#include <stack>
#include <queue>
#include "Vertex.h"
#include "Rule.h"

class Graph {
private:
    std::map<int, Vertex*> vertexList;
    std::stack<int> postOrder; //topological
    std::vector<int> test;
    std::vector<std::vector<int>> postHelper;
    std::vector<std::set<int>> forest;
    std::set<int> tree;
    std::vector<int> treev;
public:
    std::vector<std::set<int>> scc;

    void dfs(Vertex* v);
    void dfsSCC(Vertex* v);
    void dfsForestSCC(std::stack<int> post);
    std::stack<int> dfsForestPost();
    void buildDependency(Rule* rule,std::vector<Rule*> Rules);
    void addEdge(int i, int j);
    void buildGraph();
    void nameRules(Rule* rule);
    void createVertex(Rule* rule, int i);
    void toString();
    void sccToString();
    std::vector<int> ruleOrder();
    std::stack<int> getPostOrder();
    void buildReverseDependency(Graph* forwardGraph);
    std::map<int, Vertex*> getVertexList();

};
std::vector<int> Graph::ruleOrder(){
    std::vector<int> order;
    for(auto i: scc){
        for(auto j: i){
            order.push_back(j);
        }
    }

    return order;
}
std::stack<int> Graph::getPostOrder(){
    return postOrder;
}
void Graph::buildDependency(Rule* rule, std::vector<Rule*> Rules) {
    Vertex* vertex = new Vertex(rule->getID());
    std::string main = rule->getHeadPredicate()->getName();
    for(auto i: rule->predicateList){
        for(auto j: Rules){
            if(i->getName() == j->getHeadPredicate()->getName()){
                vertex->addAdjacency(j->getID());
            }
            if(rule->getHeadPredicate()->getName() == i->getName() ){
                vertex->setRecursive();
            }
        }
    }
    vertexList.insert(std::pair<int, Vertex*>(rule->getID(),vertex));
};

void Graph::buildReverseDependency(Graph* forwardGraph) {
    for(auto i: forwardGraph->vertexList){
        Vertex* vertex = new Vertex(i.first);
        vertexList.insert(std::pair<int,Vertex*>(i.first,vertex));
    }

    for(auto i: forwardGraph->vertexList){
        for(auto j: i.second->adjacencyList){
            vertexList.find(j)->second->addAdjacency(i.first);
        }
    }


};
void Graph::buildGraph(){
    dfs(vertexList.find(0)->second);
}
void Graph::addEdge(int i, int j) {
    vertexList.find(i)->second->addAdjacency(i);
}
std::stack<int> Graph::dfsForestPost() {
    for(auto i: vertexList){
        i.second->unMark();
    }
    for(auto v : vertexList){
        if(!v.second->isMarked()){
            dfs(v.second);
        }
    }
//    if(!treev.empty()){
//        postHelper.push_back(treev);
//    }
//    treev = {};
//    for(auto i: postHelper){
//        for(int j = i.size() - 1; j >=0; j--){
//            postOrder.push(i[j]);
//        }
//    }
    return postOrder;
}
void Graph::dfs(Vertex* v){
    v->mark();
    for(auto i: v->getAdjacencyList()){
        if(!vertexList.find(i)->second->isMarked()){
            dfs(vertexList.find(i)->second);
        }
    }
    postOrder.push(v->getID());
}

void Graph::dfsSCC(Vertex* v){
    v->mark();
    tree.insert(v->getID());
    for(auto i: v->getAdjacencyList()){
        if(!vertexList.find(i)->second->isMarked()){
            dfsSCC(vertexList.find(i)->second);
        }
    }
}

void Graph::dfsForestSCC(std::stack<int> post) {
    while(!post.empty()){
        auto i = post.top();
        if(!vertexList.find(i)->second->isMarked()){
            dfsSCC(vertexList.find(i)->second);
        }
        if(tree.size() > 0){
            scc.push_back(tree);
            tree = {};
        }
        post.pop();
    }
}

void Graph::toString() {
    for(auto i: vertexList){
        std::string fullString;
        fullString +=  "R" + std::to_string(i.first) + ":";
        for(auto j: i.second->getAdjacencyList()){
            fullString += "R" + std::to_string(j) + ",";
        }
        if(fullString.substr(fullString.length() - 1) == ","){
            fullString = fullString.substr(0,fullString.length() - 1);
        }
        std::cout << fullString;
        std::cout << std::endl;
    }

}


void Graph::sccToString(){
    for(auto j: scc){
        std::string fullString = "SCC: ";
        for(auto i: j){
            fullString += "R" + std::to_string(i) + ",";
        }
        if(fullString.substr(fullString.length() - 1) == ","){
            fullString = fullString.substr(0,fullString.length() - 1);
        }

        std::cout << fullString;
        std::cout << std::endl;

    }

}

std::map<int, Vertex *> Graph::getVertexList() {
    return vertexList;
}


#endif //PROJECT1_GRAPH_H
