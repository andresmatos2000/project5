//
// Created by munch on 7/1/2021.
//

#ifndef PROJECT1_ADDAUTOMATON_H
#define PROJECT1_ADDAUTOMATON_H
#include "Automaton.h"
class AddAutomaton : public Automaton
{
public:
    AddAutomaton() : Automaton(TokenType::ADD) {}  // Call the base constructor

    void S0(const std::string& input);
};

void AddAutomaton::S0(const std::string& input) {
    if (input[index] == '+') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}
#endif //PROJECT1_ADDAUTOMATON_H
