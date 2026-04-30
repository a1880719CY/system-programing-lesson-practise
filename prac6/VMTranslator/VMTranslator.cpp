#include <string>
#include <iostream>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){
    string asm_code = "";
    
    if (segment == "constant") {

        asm_code += "@" + std::to_string(offset) + "\n";
        asm_code += "D=A\n"; 

    } else if (segment == "static") {

        asm_code += "@" + std::to_string(16 + offset) + "\n";
        asm_code += "D=M\n"; 

    } else if (segment == "local") {

        asm_code += "@LCL\n";
        asm_code += "A=M\n"; 
        for (int x = 0; x < offset; ++x) {
            asm_code += "A=A+1\n"; 
        }
        asm_code += "D=M\n"; 

    } else if (segment == "argument") {

        asm_code += "@ARG\n";
        asm_code += "A=M\n"; 
        for (int x = 0; x < offset; ++x) {
            asm_code += "A=A+1\n"; 
        }
        asm_code += "D=M\n"; 

    } else if (segment == "this") {

        asm_code += "@THIS\n";
        asm_code += "A=M\n"; 
        for (int x = 0; x < offset; ++x) {
            asm_code += "A=A+1\n"; 
        }
        asm_code += "D=M\n"; 

    } else if (segment == "that") {

        asm_code += "@THAT\n";
        asm_code += "A=M\n"; 
        for (int x = 0; x < offset; ++x) {
            asm_code += "A=A+1\n"; 
        }
        asm_code += "D=M\n"; 

    } else if (segment == "pointer") {
        
        asm_code += "@" + std::to_string(3 + offset) + "\n"; 
        asm_code += "D=M\n";

    } else if (segment == "temp") {

        asm_code += "@" + std::to_string(5 + offset) + "\n"; 
        asm_code += "D=M\n"; 

    }

    asm_code = asm_code + "@SP\n" + "AM=M+1\n" + "A=A-1\n" + "M=D\n";

    return asm_code;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){
    string asm_code = "@SP\nAM=M-1\nD=M\n";

    if (segment == "static") {

        asm_code += "@" + std::to_string(16 + offset) + "\n";

    } else if (segment == "local") {

        asm_code += "@LCL\n";
        asm_code += "A=M\n"; 
        for (int x = 0; x < offset; ++x) {
            asm_code += "A=A+1\n"; 
        }

    } else if (segment == "argument") {

        asm_code += "@ARG\n";
        asm_code += "A=M\n"; 
        for (int x = 0; x < offset; ++x) {
            asm_code += "A=A+1\n"; 
        }

    } else if (segment == "this") {

        asm_code += "@THIS\n";
        asm_code += "A=M\n"; 
        for (int x = 0; x < offset; ++x) {
            asm_code += "A=A+1\n"; 
        } 

    } else if (segment == "that") {

        asm_code += "@THAT\n";
        asm_code += "A=M\n"; 
        for (int x = 0; x < offset; ++x) {
            asm_code += "A=A+1\n"; 
        }

    } else if (segment == "pointer") {
        
        asm_code += "@" + std::to_string(3 + offset) + "\n"; 

    } else if (segment == "temp") {

        asm_code += "@" + std::to_string(5 + offset) + "\n"; 
         
        
    }

    asm_code += "M=D\n"; 

    return asm_code;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    string asm_code = "";
        
    asm_code += "@SP\n";
    asm_code += "AM=M-1\n";
    asm_code += "D=M\n";
    asm_code += "A=A-1\n";
    asm_code += "M=M+D\n";
    
    return asm_code;
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    string asm_code = "";
        
    asm_code += "@SP\n";
    asm_code += "AM=M-1\n";
    asm_code += "D=M\n";
    asm_code += "A=A-1\n";
    asm_code += "M=M-D\n";
    
    return asm_code;
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    string asm_code = "";
        
    asm_code += "@SP\n";
    asm_code += "A=M-1\n";
    asm_code += "M=-M\n";
    
    return asm_code;

}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    string asm_code = "";
        
    asm_code += "@SP\n";
    asm_code += "A=M-1\n";
    asm_code += "D=M\n";
    asm_code += "A=A-1\n";
    asm_code += "D=D-M\n";
    asm_code += "@YES\n";
    asm_code += "D;JEQ\n";
    asm_code += "D=0\n";
    asm_code += "@LAST\n";
    asm_code += "0;JMP\n";

    //yes
    asm_code += "(YES)\n";
    asm_code += "D=-1\n";
    asm_code += "@LAST\n";
    asm_code += "0;JMP\n";

    //when outputing
    asm_code += "(LAST)\n";
    asm_code += "@SP\n";
    asm_code += "A=M\n";
    asm_code += "M=D\n";
    asm_code += "@SP\n";
    asm_code += "M=M+1\n";
    
    return asm_code;
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    return "";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    return "";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    string asm_code = "";
        
    asm_code += "@SP\n";
    asm_code += "AM=M-1\n";
    asm_code += "D=M\n";
    asm_code += "A=A-1\n";
    asm_code += "M=M&D\n";
    
    return asm_code;
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    string asm_code = "";
        
    asm_code += "@SP\n";
    asm_code += "AM=M-1\n";
    asm_code += "D=M\n";
    asm_code += "A=A-1\n";
    asm_code += "M=M|D\n";
    
    return asm_code;
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "("+label+")";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    string asm_code = "";
        
    asm_code += "@"+label+"\n";
    asm_code += "0;JMP\n";
    
    return asm_code;
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    string asm_code = "";

    asm_code += "@SP\n";
    asm_code += "AM=M-1\n";
    asm_code += "D=M\n";
    asm_code += "@"+label+"\n";
    asm_code += "D;JNE\n";

    return asm_code;
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    string asm_code = "(" + function_name + ")\n";

    for (int x = 0; x < n_vars; ++x) {

        asm_code += "@0\n";
        asm_code += "D=A\n";
        asm_code += "@SP\n";
        asm_code += "AM=M+1\n";
        asm_code += "A=A-1\n";
        asm_code += "M=D\n";

    }

    return asm_code;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    static int call_counter = 0;
    string return_label = function_name + "$ret." + to_string(call_counter++);
    string asm_code = "@" + return_label + "\n";
    asm_code += "D=A\n";
    asm_code += "@SP\n";
    asm_code += "AM=M+1\n";
    asm_code += "A=A-1\n";
    asm_code += "M=D\n";

    // Save LCL, ARG, THIS, THAT
    asm_code += "@LCL\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    asm_code += "@ARG\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    asm_code += "@THIS\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    asm_code += "@THAT\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";

    // Reposition ARG = SP - n_args - 5
    asm_code += "@SP\nD=M\n@5\nD=D-A\n";
    asm_code += "@" + to_string(n_args) + "\n";
    asm_code += "D=D-A\n";
    asm_code += "@ARG\nM=D\n";

    // Set LCL = SP
    asm_code += "@SP\nD=M\n@LCL\nM=D\n";

    // Goto the function
    asm_code += "@" + function_name + "\n";
    asm_code += "0;JMP\n";

    // Declare return label
    asm_code += "(" + return_label + ")\n";

    return asm_code;
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    string asm_code = "@LCL\nD=M\n@R13\nM=D\n";  // Save FRAME = LCL
    asm_code += "@5\nA=D-A\nD=M\n@R14\nM=D\n";  // Save RET = *(FRAME-5)

    // Reposition the return value for the caller
    asm_code += "@SP\nA=M-1\nD=M\n@ARG\nA=M\nM=D\n";

    // Restore SP = ARG + 1
    asm_code += "@ARG\nD=M+1\n@SP\nM=D\n";

    // Restore THAT, THIS, ARG, LCL
    asm_code += "@R13\nA=M-1\nD=M\n@THAT\nM=D\n";
    asm_code += "@R13\nD=M\n@2\nA=D-A\nD=M\n@THIS\nM=D\n";
    asm_code += "@R13\nD=M\n@3\nA=D-A\nD=M\n@ARG\nM=D\n";
    asm_code += "@R13\nD=M\n@4\nA=D-A\nD=M\n@LCL\nM=D\n";

    // Goto RET
    asm_code += "@R14\nA=M\n0;JMP\n";

    return asm_code;
}