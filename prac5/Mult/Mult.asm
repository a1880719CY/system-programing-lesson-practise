// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@R0
M=0

// Check the sign of R1
@R1
D=M
@R1POS
D;JGE          // If R1 >= 0, jump to R1POS

// R1 is negative
@R1
M=-M           // Make R1 positive
@sign
M=1            // Set sign to 1 (result will be negative)

(R1POS)
@R2
D=M
@R2POS
D;JGE          // If R2 >= 0, jump to R2POS

// R2 is negative
@R2
M=-M           // Make R2 positive
@sign
D=M
@temp          // Use a temporary variable to avoid overwriting sign
D=D+1          // Increment if sign was already set
@sign
M=D            // Update sign

(R2POS)
@R2
D=M
@ZERO
D;JEQ          // If R2 is 0, result is 0, skip to END

(LOOP)
    @R2
    MD=M-1      // Decrement R2
    @R1
    D=M
    @R0
    M=M+D        // Add R1 to the result
    @R2
    D=M
    @LOOP
    D;JGT        // If R2 > 0, continue the loop

// Check if the result should be negative
@sign
D=M
@END
D=D-1
D;JNE          // If sign is 0, skip negation

@R0
M=-M           // Negate the result if the sign is set

(END)
@END
0;JMP

(ZERO)
@R0
M=0
@END
0;JMP




