#include "CompilerParser.h"


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokenn = tokens;
    indexx = 0;
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

    ParseTree* xxxxx = new ParseTree("class", "");
    //std::cout << "current:" << current()->tostring() << std::endl;
    if(have("keyword", "class") == true){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(var() == true){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(have("symbol","{") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    // class variable 
    while(have("keyword","static") || have("keyword","field")){
       xxxxx->addChild(compileClassVarDec());
    }

    // body function 
    while(have("keyword","constructor") || have("keyword","function") || have("keyword","method")){
       xxxxx->addChild(compileSubroutine());
    }

    if(have("symbol","}") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }   

    return xxxxx;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* xxxxx = new ParseTree("classVarDec","");
    
    if(have("keyword","static") || have("keyword","field")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(typee()){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(var() == true){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }
    
    // ","
    while(indexx<tokenn.size() && have("symbol",",")){

        if(have("symbol",",")){
            xxxxx->addChild(current());
            next();

        }else{
            throw ParseException();
        }

        if(var() == true){
            xxxxx->addChild(current());
            next();
        }else{
            throw ParseException();
        }
    }

    if(have("symbol",";") == true){
            xxxxx->addChild(current());
            next();

        }else{
            throw ParseException();
        }
    return xxxxx;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* xxxxx = new ParseTree("subroutine","");

    xxxxx->addChild(current());
    next();

    if(typee() || have("keyword","void")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(var()){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(have("symbol","(")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    xxxxx->addChild(compileParameterList());

    if(have("symbol",")")){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    xxxxx->addChild(compileSubroutineBody());

    return xxxxx;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* xxxxx = new ParseTree("parameterList","");
    
    if(typee()){
        
        if(typee() == true){
            xxxxx->addChild(current());
            next();
        }else{
            throw ParseException();
        }

        if(var() == true){
            xxxxx->addChild(current());
            next();
        }else{
            throw ParseException();
        }
        
        while(indexx<tokenn.size() && have("symbol",",")){

            if(have("symbol",",")){
                xxxxx->addChild(current());
                next();

            }else{
                throw ParseException();
            }

            if(typee() == true){
                xxxxx->addChild(current());
                next();
            }else{
                throw ParseException();
            }

            if(var() == true){
                xxxxx->addChild(current());
                next();
            }else{
                throw ParseException();
            }
        }
    }
    return xxxxx;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* xxxxx = new ParseTree("subroutineBody","");

    if(have("symbol","{") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    // varDec
    while(have("keyword","var")){
       xxxxx->addChild(compileVarDec());
    }

    // statements
    xxxxx->addChild(compileStatements());

    if(have("symbol","}") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }
    return xxxxx;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* xxxxx = new ParseTree("varDec","");

    if(have("keyword","var")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(typee() == true){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }
    
    if(var() == true){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    // ","
    while(indexx<tokenn.size() && have("symbol",",")){

        if(have("symbol",",")){
            xxxxx->addChild(current());
            next();

        }else{
            throw ParseException();
        }

        if(var() == true){
            xxxxx->addChild(current());
            next();
        }else{
            throw ParseException();
        }
    }

    if(have("symbol",";") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    return xxxxx;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* xxxxx = new ParseTree("statements","");

    while (indexx<tokenn.size() && (have("keyword","let") || have("keyword","if") || have("keyword","while") || have("keyword","do") || have("keyword","return"))){
        
        if(have("keyword","let")){
            xxxxx->addChild(compileLet());

        }else if(have("keyword","if")){
            xxxxx->addChild(compileIf());

        }else if(have("keyword","while")){
            xxxxx->addChild(compileWhile());

        }else if(have("keyword","do")){
            xxxxx->addChild(compileDo());

        }else if(have("keyword","return")){
            xxxxx->addChild(compileReturn());
        }
    }
    
    return xxxxx;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* xxxxx = new ParseTree("letStatement","");

    if(have("keyword","let")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(var() == true){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(have("symbol","[")){
        
        if(have("symbol","[")){
            xxxxx->addChild(current());
            next();
        }else{
            throw ParseException();
        }

        xxxxx->addChild(compileExpression());

        if(have("symbol","]")){
            xxxxx->addChild(current());
            next();
        }else{
            throw ParseException();
        }
    }

    if(have("symbol","=")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    xxxxx->addChild(compileExpression());

    if(have("symbol",";") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    return xxxxx;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* xxxxx = new ParseTree("ifStatement","");

    if(have("keyword","if")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(have("symbol","(") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    xxxxx->addChild(compileExpression());

    if(have("symbol",")") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    if(have("symbol","{") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    xxxxx->addChild(compileStatements());

    if(have("symbol","}") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    if(indexx<tokenn.size() && have("keyword","else")){
        if(have("keyword","else")){
            xxxxx->addChild(current());
            next();

        }else{
            throw ParseException();
        }

        if(have("symbol","{") == true){
            xxxxx->addChild(current());
            next();

        }else{
            throw ParseException();
        }

        xxxxx->addChild(compileStatements());

        if(have("symbol","}") == true){
            xxxxx->addChild(current());
            next();

        }else{
            throw ParseException();
        }
    }

    return xxxxx;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    ParseTree* xxxxx = new ParseTree("whileStatement","");
    if(have("keyword","while")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(have("symbol","(") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    xxxxx->addChild(compileExpression());

    if(have("symbol",")") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    if(have("symbol","{") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    xxxxx->addChild(compileStatements());

    if(have("symbol","}") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    return xxxxx;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* xxxxx = new ParseTree("doStatement","");

    if(have("keyword","do")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    xxxxx->addChild(compileExpression());

    if(have("symbol",";") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    return xxxxx;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* xxxxx = new ParseTree("returnStatement","");

    if(have("keyword","return")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    if(have("keyword","skip")){
        xxxxx->addChild(compileExpression());
    }

    if(have("symbol",";") == true){
        xxxxx->addChild(current());
        next();

    }else{
        throw ParseException();
    }

    return xxxxx;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    ParseTree* xxxxx = new ParseTree("expression","");

    if(have("keyword","skip")){
        xxxxx->addChild(current());
        next();
    }else{
        throw ParseException();
    }

    return xxxxx;
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
    indexx++;
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    std::list<Token*>::iterator it = tokenn.begin();

    std::advance(it, indexx); // Move the iterator 3 positions

    if (it != tokenn.end()) {
        Token* thirdValue = *it;
        return thirdValue
    }
    return NULL;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    if(current()->getType() == expectedType && current()->getValue == expectedValue ){
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
    if(current()->getType() == expectedType && current()->getValue == expectedValue ){
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
bool CompilerParser::typee(){
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

