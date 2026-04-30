#include "CompilerParser.h"

using namespace std;


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokenIn = tokens;
    indexIn = 0;
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    return compileClass();
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {

    ParseTree* tempTree = new ParseTree("class", "");

    if(have("keyword", "class")){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(var()){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(have("symbol","{")){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    while(have("keyword","static") || have("keyword","field")){
       tempTree->addChild(compileClassVarDec());
    }

    while(have("keyword","constructor") || have("keyword","function") || have("keyword","method")){
       tempTree->addChild(compileSubroutine());
    }

    if(have("symbol","}")){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }   

    return tempTree;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* tempTree = new ParseTree("classVarDec","");
    
    if(have("keyword","static") || have("keyword","field")){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(typeFun()){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(var() == true){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }
    
    // ","
    while(indexIn<tokenIn.size() && have("symbol",",")){

        if(have("symbol",",")){
            tempTree->addChild(current());
            next();

        }else{
            throw ParseException();
        }

        if(var() == true){
            tempTree->addChild(current());
            next();
        }else{
            throw ParseException();
        }
    }

    if(have("symbol",";") == true){
            tempTree->addChild(current());
            next();

        }else{
            throw ParseException();
        }
    return tempTree;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* tempTree = new ParseTree("subroutine","");

    tempTree->addChild(current());
    next();

    if(typeFun() || have("keyword","void") == true){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(var() == true){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(have("symbol","(") == true){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    tempTree->addChild(compileParameterList());

    if(have("symbol",")") == true){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    tempTree->addChild(compileSubroutineBody());

    return tempTree;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* tempTree = new ParseTree("parameterList","");
    
    if(typeFun()){
        
        if(typeFun() == true){
            tempTree->addChild(current());
            next();
        }else{
            throw ParseException();
        }

        if(var() == true){
            tempTree->addChild(current());
            next();
        }else{
            throw ParseException();
        }
        
        while(indexIn<tokenIn.size() && have("symbol",",")){

            if(have("symbol",",")){
                tempTree->addChild(current());
                next();

            }else{
                throw ParseException();
            }

            if(typeFun() == true){
                tempTree->addChild(current());
                next();
            }else{
                throw ParseException();
            }

            if(var() == true){
                tempTree->addChild(current());
                next();
            }else{
                throw ParseException();
            }
        }
    }
    return tempTree;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* tempTree = new ParseTree("subroutineBody","");

    if(have("symbol","{")){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    while(have("keyword","var")){
       tempTree->addChild(compileVarDec());
    }

    tempTree->addChild(compileStatements());

    if(have("symbol","}")){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }
    return tempTree;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* tempTree = new ParseTree("varDec","");

    if(have("keyword","var")){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(typeFun()){
        tempTree->addChild(current());
        next();
    } else {
        throw ParseException();
    }
    
    if(var()){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    while(indexIn<tokenIn.size() && have("symbol",",")){

        if(have("symbol",",")){
            tempTree->addChild(current());
            next();

        }else{
            throw ParseException();
        }

        if(var()){
            tempTree->addChild(current());
            next();
        }else{
            throw ParseException();
        }
    }

    if(have("symbol",";")){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    return tempTree;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* tempTree = new ParseTree("statements","");

    while (indexIn<tokenIn.size() && (have("keyword","let") || have("keyword","if") || have("keyword","while") || have("keyword","do") || have("keyword","return"))){
        
        if(have("keyword","let") == true){

            tempTree->addChild(compileLet());

        }else if(have("keyword","if") == true){

            tempTree->addChild(compileIf());

        }else if(have("keyword","while") == true){

            tempTree->addChild(compileWhile());

        }else if(have("keyword","do") == true){

            tempTree->addChild(compileDo());

        }else if(have("keyword","return") == true){

            tempTree->addChild(compileReturn());
        }
    }
    
    return tempTree;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* tempTree = new ParseTree("letStatement","");

    if(have("keyword","let")){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(var() == false){
        throw ParseException();
    }else{
        tempTree->addChild(current());
        next();
    }

    if(have("symbol","[")){
        
        if(have("symbol","[")){
            tempTree->addChild(current());
            next();
        }else{
            throw ParseException();
        }

        tempTree->addChild(compileExpression());

        if(have("symbol","]")){
            tempTree->addChild(current());
            next();
        }else{
            throw ParseException();
        }
    }

    if(have("symbol","=")){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    tempTree->addChild(compileExpression());

    if(have("symbol",";") == false){
        throw ParseException();

    }else{
        tempTree->addChild(current());
        next();
    }

    return tempTree;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* tempTree = new ParseTree("ifStatement","");

    if(have("keyword","if")){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(have("symbol","(")){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    tempTree->addChild(compileExpression());

    if(have("symbol",")")){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    if(have("symbol","{")){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    tempTree->addChild(compileStatements());

    if(have("symbol","}")){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    if(indexIn<tokenIn.size() && have("keyword","else")){
        if(have("keyword","else")){
            tempTree->addChild(current());
            next();

        }else{
            throw ParseException();
        }

        if(have("symbol","{")){
            tempTree->addChild(current());
            next();

        }else{
            throw ParseException();
        }

        tempTree->addChild(compileStatements());

        if(have("symbol","}")){
            tempTree->addChild(current());
            next();

        }else{
            throw ParseException();
        }
    }

    return tempTree;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    ParseTree* tempTree = new ParseTree("whileStatement","");
    if(have("keyword","while")){

        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    if(have("symbol","(")){

        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    tempTree->addChild(compileExpression());

    if(have("symbol",")")){

        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    if(have("symbol","{")){

        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    tempTree->addChild(compileStatements());

    if(have("symbol","}")){

        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    return tempTree;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* tempTree = new ParseTree("doStatement","");

    if(have("keyword","do")){

        tempTree->addChild(current());
        next();

    }else{

        throw ParseException();
    }

    tempTree->addChild(compileExpression());

    if(have("symbol",";")){

        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    return tempTree;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* tempTree = new ParseTree("returnStatement","");

    if(have("keyword","return") == true){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(have("keyword","skip") == true){
        tempTree->addChild(compileExpression());
    }

    if(have("symbol",";") == true){
        tempTree->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    return tempTree;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    ParseTree* tempTree = new ParseTree("expression","");

    if(have("keyword","skip")){
        tempTree->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    return tempTree;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    indexIn++;
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    list<Token*>::iterator it = tokenIn.begin();

    std::advance(it, indexIn);

    if (it != tokenIn.end()) {
        Token* thirdValue = *it;
        return thirdValue;
    }
    return NULL;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(string expectedType, string expectedValue){
    if(current()->getType() == expectedType && current()->getValue() == expectedValue ){
        return true;
    }
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if(current()->getType() == expectedType && current()->getValue() == expectedValue ){
        return current();
    }
    return NULL;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
void CompilerParser::current_dd(){

}
bool CompilerParser::typeFun(){
    if((current()->getType() == "keyword" && current()->getValue() == "int") || (current()->getType() == "keyword" && current()->getValue() == "char")
    ||(current()->getType() == "keyword" && current()->getValue() == "boolean") || var()){
        return true;
    }
    return false;
}

bool CompilerParser::var(){
    if(current()->getType() == "identifier"){
        return true;
    }
    return false;
}
