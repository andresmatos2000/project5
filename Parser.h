//
// Created by munch on 7/3/2021.
//

#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H
#include "Token.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include <vector>

class Parser {
public:
    DatalogProgram* datalog = new DatalogProgram();
    DatalogProgram* getDatalog();
    void parse(std::vector<Token*> tokens);
    Parser(std::vector<Token*> tokenList){
        this->index = 0;
        this->current = tokenList[0];
        this->current = tokenList[0];
        parse(tokenList);
    };
    ~Parser(){
        //std::cout << "In deconstructor" <<std::endl;
    }
private:

    std::vector<Token*> tokens;
    Predicate* PredicateHolder;
    Rule* RuleHolder;
    Token* current;
    int index = 0;
    void datalogProgram();
    void parsePredicate();
    void parseScheme();
    void parseSchemeList();
    void parseFactList();
    void parseFact();
    void parseRuleList();
    void parseQueryList();
    void parseQuery();
    void parseRule();
    void parseHeadPredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    void parseParameter();
    void parseEOF();
    bool matchToken(TokenType tokenType);

};
bool Parser::matchToken(TokenType tokenType){

    if(tokenType == current->getType()){
        index++;
        current = tokens[index];
        return true;
    }
    else{
        return false;

    }
}
void Parser::parse(std::vector<Token *> tokenList) {
    this->tokens = tokenList;

    //std::cout << std::endl;
//    for(unsigned int i = 0; i < tokens.size(); i++){
//        std::cout << tokens[i]->tokenTypeToString(tokens[i]->getType()) << std::endl;
//    }
    bool exceptionCaught = false;
    try {
        datalogProgram();
    } catch (std::string error) {
        std::cout << "Failure!" << std::endl << "  " << error;
        exceptionCaught = true;
    }
    if(!exceptionCaught){
        //std::cout << "Success!" << std::endl;
        datalog->parseHelper();
        //std::cout << datalog->To_String();
    }
}
void Parser::datalogProgram(){
    matchToken(TokenType::SCHEMES);
    matchToken(TokenType::COLON);
    parseScheme();
    parseSchemeList();
    if(current->getType() != TokenType::FACTS)
        throw current->To_String();
    matchToken(TokenType::FACTS);
    matchToken(TokenType::COLON);
    parseFactList();
    if(current->getType() != TokenType::RULES)
        throw current->To_String();
    matchToken(TokenType::RULES);
    matchToken(TokenType::COLON);
    parseRuleList();
    matchToken(TokenType::QUERIES);
    matchToken(TokenType::COLON);
    parseQuery();
    parseQueryList();
    parseEOF();
}
void Parser::parseSchemeList() {
    if(current->getType() == TokenType::ID){
        //std::cout << current->tokenTypeToString(current->getType()) <<std::endl;
        parseScheme();
    } else if(current->getType() == TokenType::ID) {
        parseSchemeList();
    }
}
//ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::parseScheme() {
    if(current->getType() == TokenType::ID)
        PredicateHolder = new Predicate(current->getDescription());
    else
        throw current->To_String();
    //std::cout << "parsePredicate " << current->getDescription() << std::endl;
    matchToken(TokenType::ID);
    matchToken(TokenType::LEFT_PAREN);
    if(current->getType() == TokenType::ID){
        PredicateHolder->addParameter(new Parameter(current->getType(),current->getDescription()));
    } else throw current->To_String();
    matchToken(TokenType::ID);
    parseIdList();
    matchToken(TokenType::RIGHT_PAREN);
    datalog->addScheme(PredicateHolder);
    if(current->getType() == TokenType::ID){
        parseSchemeList();
    };
    //std::cout << "Matched a predicate" << std::endl;
}
//COMMA ID idList | lambda
void Parser::parseIdList() {
    matchToken(TokenType::COMMA);
    if(current->getType() == TokenType::ID) {
        PredicateHolder->addParameter(new Parameter(current->getType(),current->getDescription()));
        matchToken(current->getType());
        parseIdList();
    }

}
void Parser::parseFactList() {
    //std::cout << "Fact List" << std::endl;
    if(current->getType() == TokenType::ID) {
        parseFact();
        if (current->getType() == TokenType::ID) {
            parseFactList();
        }
    }
}
//ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
void Parser::parseFact(){
    PredicateHolder = new Predicate(current->getDescription());
    //std::cout << "parsePredicate " << current->getDescription() << std::endl;
    matchToken(TokenType::ID);
    matchToken(TokenType::LEFT_PAREN);
    if(current->getType() == TokenType::STRING){
        PredicateHolder->addParameter(new Parameter(current->getType(),current->getDescription()));
    }
    matchToken(TokenType::STRING);
    if(current->getType() == TokenType::COMMA){
        parseStringList();
    }
    matchToken(TokenType::RIGHT_PAREN);
    if(current->getType() == TokenType::PERIOD){
        matchToken(TokenType::PERIOD);
        datalog->addFact(PredicateHolder);
    }
    else {
        throw current->To_String();
    }

    //std::cout << "Matched a predicate" << std::endl;
}
//stringList	-> 	COMMA STRING stringList | lambda
void Parser::parseStringList() {
    matchToken(TokenType::COMMA);
    if(current->getType() == TokenType::STRING) {
        PredicateHolder->addParameter(new Parameter(current->getType(),current->getDescription()));
        matchToken(current->getType());
        parseStringList();
    }
}
void Parser::parseRuleList() {
    //std::cout << "Rule List" << std::endl;
    if(current->getType() == TokenType::ID){
        parseRule();
        if(current->getType() == TokenType::ID){
            parseRuleList();
        }
    }
}

//headPredicate COLON_DASH predicate predicateList PERIOD
void Parser::parseRule() {
    parseHeadPredicate();
    matchToken(TokenType::COLON_DASH);
    parsePredicate();
    parsePredicateList();
    matchToken(TokenType::PERIOD);
    datalog->addRule(RuleHolder);
}
//ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::parseHeadPredicate() {
    PredicateHolder = new Predicate(current->getDescription());
   // std::cout << "parsePredicate " << current->getDescription() << std::endl;
    matchToken(TokenType::ID);
    matchToken(TokenType::LEFT_PAREN);
    if(current->getType() == TokenType::ID){
        PredicateHolder->addParameter(new Parameter(current->getType(),current->getDescription()));
    }
    matchToken(TokenType::ID);
    parseIdList();
    matchToken(TokenType::RIGHT_PAREN);
    RuleHolder = new Rule(PredicateHolder);
    //std::cout << "Matched a predicate" << std::endl;

}
//COMMA predicate predicateList | lambda
void Parser::parsePredicateList() {
    if(current->getType() == TokenType::COMMA){
        matchToken(TokenType::COMMA);
        parsePredicate();
        if(current->getType() == TokenType::COMMA){
            parsePredicateList();
        }
    }
}
//ID LEFT_PAREN parameter parameterList RIGHT_PAREN
void Parser::parsePredicate(){
    if(current->getType() == TokenType::ID){
        PredicateHolder = new Predicate(current->getDescription());
    }
    matchToken(TokenType::ID);
    matchToken(TokenType::LEFT_PAREN);
    parseParameter();
    parseParameterList();
    matchToken(TokenType::RIGHT_PAREN);
    RuleHolder->addPredicate(PredicateHolder);
}
//parameter	->	STRING | ID
void Parser::parseParameter() {
    //std::cout << "parseParameter" << current->tokenTypeToString(current->getType()) << std::endl;
    if((current->getType() == TokenType::STRING) || (current->getType() == TokenType::ID)){
        PredicateHolder->addParameter(new Parameter(current->getType(),current->getDescription()));
        matchToken(current->getType());
    } else {
        throw current->To_String();
    }
}
//COMMA parameter parameterList | lambda
void Parser::parseParameterList() {
    if(current->getType() == TokenType::COMMA){
        matchToken(TokenType::COMMA);
        parseParameter();
        parseParameterList();
    }
}
//query queryList | lambda
void Parser::parseQueryList() {
    if(current->getType() == TokenType::ID){
        //std::cout << current->tokenTypeToString(current->getType()) <<std::endl;
        parseQuery();
        if(current->getType() == TokenType::ID) {
            parseQueryList();
        }
    }
}
//predicate Q_MARK
void Parser::parseQuery(){
    if(current->getType() == TokenType::ID)
        RuleHolder = new Rule(PredicateHolder);
    else
        throw current->To_String();
    parsePredicate();
    matchToken(TokenType::Q_MARK);
    datalog->addQuery(PredicateHolder);
}

void Parser::parseEOF(){
    //std::cout << "Parse EOF" << std::endl;
    if(current->getType() == TokenType::TYPE_EOF) {
        matchToken(TokenType::TYPE_EOF);
    } else {
        throw current->To_String();
    }
}

DatalogProgram* Parser::getDatalog(){
    return datalog;
}


#endif //PROJECT1_PARSER_H
