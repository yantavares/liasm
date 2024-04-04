       INPUT   N
       LOAD    N
FAT:   SUB     ONE
       JUMPZ   FIM
       STORE   AUX
       MULT    N
       STORE   N
       LOAD    AUX
       JUMP    FAT
FIM:   OUTPUT  N
       STOP
AUX:   SPACE
N:     SPACE
ONE:   CONST   1
