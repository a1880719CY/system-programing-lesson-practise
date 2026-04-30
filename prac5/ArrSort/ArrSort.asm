// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@R1
D=M
@R2
D=D+M
@R2
M=D

(OUTER_LOOP)
@R1
D=M
@R2
D=D-M
@FINISH
D;JGE

@R1
D=M
@R3
M=D+1

(INNER_LOOP)
@R3
D=M
@R2
D=D-M
@INNER_END
D;JGE

@R3
A=M
D=M

@R1
A=M
D=D-M
@SKIP_SWAP
D;JGE

(SWAP)
@R1
A=M
D=M
@temp
M=D
@R3
A=M
D=M
@R1
A=M
M=D
@temp
D=M
@R3
A=M
M=D

(SKIP_SWAP)
@R3
M=M+1
@INNER_LOOP
0;JMP

(INNER_END)
@R1
M=M+1
@OUTER_LOOP
0;JMP

(FINISH)
@R0
M=-1
(END)
@END
0;JMP








