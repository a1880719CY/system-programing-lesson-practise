load AddSub.asm,
output-file AddSub02.out,
compare-to AddSub02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[3]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0 initially to 0
set RAM[1] 8,  // Set R1 = 8
set RAM[2] 5,  // Set R2 = 5
set RAM[3] 1;  // Set R3 = 1 for subtraction

repeat 100 {
  ticktock;    // Run for 100 clock cycles
}

// Restore original values in case the program changed them
set RAM[1] 8,
set RAM[2] 5,
set RAM[3] 1,

output;        // Output the result to file