// Sample Test file for Abs.asm
// Follows the Test Scripting Language format described in 
// Appendix B of the book "The Elements of Computing Systems"

load Abs.asm,
output-file Abs01.out,
compare-to Abs01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2;

set PC 0,
set RAM[0] 0,  
set RAM[1] -5; 
repeat 100 {
  ticktock;    
}
set RAM[1] -5,
output;