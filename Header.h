//
// Created by munch on 7/12/2021.
//

#ifndef PROJECT1_HEADER_H
#define PROJECT1_HEADER_H
#include <vector>
#include "Predicate.h"
class Header {
private:
    std::vector<std::string> headerList;
public:
    Header(Predicate* predicate){
        for(auto i: predicate->getParameters()){
           headerList.push_back(i->To_String());
        };
    };
    Header(Header* header){
        this->headerList = header->headerList;
    }
    Header(std::vector<std::string> headerList){
        this->headerList = headerList;
    }
    void addHeader(std::string name);
    void changeHeader(std::string string, int index);
    std::vector<int>  fixHeader(std::map<int, std::string> variables);
    void setHeader(std::vector<std::string> newHeader);

        void toString();
    std::string getValue(int i);
    std::vector<std::string> getHeaderList();
    int getSize();

};
int Header::getSize(){
    return this->headerList.size();
}
std::vector<std::string> Header::getHeaderList(){
    return this->headerList;
}
void Header::addHeader(std::string name) {
    headerList.push_back(name);
};

std::vector<int> Header::fixHeader(std::map<int, std::string> variables) {
    std::vector<std::string> newHeaderList;
    std::vector<int> indexesSaved;
    for(auto i: variables){
        bool seen = false;
        for(auto j: newHeaderList){
            if(j == i.second) {
                seen = true;
                break;
            }
            else indexesSaved.push_back(i.first);
        }
        if(seen)
            ;
        else
        newHeaderList.push_back(headerList[i.first]);
    }
    headerList = newHeaderList;
    return indexesSaved;
}
void Header::changeHeader(std::string string,int index) {
    headerList[index] = string;
};
void Header::setHeader(std::vector<std::string> newHeader){
    this->headerList = newHeader;
}
void Header::toString(){
    for(auto i: headerList){
        std::cout << i + " ";
    }
}
std::string Header::getValue(int i){
    return headerList[i];
}


#endif //PROJECT1_HEADER_H
