// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@R2          
D=M          
@END_CHECK    
D;JLE

@R1          
D=M-1        
@R2          
M=M+D        

@32767       
D=A          
@R0          
M=D          

(LOOP)
(CHECK_TERMINATE)
    @R1      
    D=M      
    @R2      
    D=D-M    
    @END     
    D;JGT    

    @R1      
    A=M      
    D=M      

    @POSITIVE_CHECK
    D;JGE    

    @NEGATIVE_CHECK
    0;JMP    

(POSITIVE_CHECK)
    @R0
    D=D-M    
    @SKIP
    D;JGE    

(UPDATE_SMALLEST)
    @R1      
    A=M      
    D=M      
    @R0      
    M=D      

(SKIP)
    @R1      
    M=M+1    
    @LOOP    
    0;JMP    

(END)
    @END
    0;JMP    

(NEGATIVE_CHECK)
    @R0
    D=M      
    @NEGATIVE_UPDATE
    D;JLT    

    @UPDATE_SMALLEST
    0;JMP    

(NEGATIVE_UPDATE)
    @R1
    A=M      
    D=M      
    @R0
    D=D-M    
    @SKIP
    D;JGE    

    @UPDATE_SMALLEST  
    0;JMP

(END_CHECK)
    @R0
    M=0        
    @END
    0;JMP  





