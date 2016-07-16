MOVA
MOVEC ;WE CAN READ THE DATA.
MOVEX @DPTR , A ; THE MOVES IS JUST FOR RAM OUT.
XCHA ;THE DATA EXCANGE .
XCHA 40H ; XCHA is exchange . ex -> X ,  exchange the value .
SWAP ; It does mean the exchange .
SWAP A ; assign the a = 3FH . the after the swap , it
becomes F3H
PUSH ; The stack's operation .
PUSH 50H;Assign the 20H is 78H
POP ACC ; The operation is just for the stack and fetch the
data from the stack .
;And after the line . we fetch the data from the stack and
the pop-- .
ANL A , R0; The logic is just for & .
;The line is for A = A&R0
ORL ;Just for the or
XRL ;Just for the ^
ADD
SUB
DIV
MULIT
MOD
ADD A , 4;
ADDC C , 40H ; Just for A+()
SUBB A , R7 ; substract with bore .
INC
DEC
MUL AB ; is just A * B -> BA
DIV AB ; The operation is just for the form like A / B -> A
A % B -> B
DA A ; 8421 BCD CODE . AND WE CAN KNOW WE SHOULD	
JNC ; cy = 0 , and we move it . if if cy = 1 .
