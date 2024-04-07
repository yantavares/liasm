       LOAD    LIMIT          ; Input the limit for Fibonacci sequence
       LOAD    ZERO           ; Load the initial Fibonacci number (0) to ACC
       STORE   CUR            ; Store 0 in CUR
       LOAD    ONE            ; Load the second Fibonacci number (1) to ACC
       STORE   PREV           ; Store 1 in PREV (current becomes previous for the next iteration)
       STORE   TEMP           ; Store 1 in TEMP (this is the first number to be output)
       
FIB:   LOAD    CUR            ; Load the current Fibonacci number
       ADD     PREV           ; Add the previous Fibonacci number to ACC (calculating next Fibonacci number)
       STORE   TEMP           ; Store the result temporarily
       LOAD    PREV           ; Load the previous number into ACC
       STORE   CUR            ; Move it into CUR (this is the old current number)
       LOAD    TEMP           ; Load the new Fibonacci number into ACC
       STORE   PREV           ; Store it in PREV (this is now the current number for the next iteration)
       SUB     LIMIT          ; Subtract LIMIT from the current Fibonacci number
       JMPP    END            ; If the result is positive, we've reached the limit, end
       JMP     FIB            ; Otherwise, continue calculating the sequence
       
END:   LOAD    CUR
       SUB     VALUE
       JMPZ   OK
       THROW 
OK:    STOP

; Variables and constants
PREV:  SPACE                  ; Space for the previous Fibonacci number
CUR:   SPACE                  ; Space for the current Fibonacci number
TEMP:  SPACE                  ; Temporary storage for the new Fibonacci number
LIMIT: CONST  10              ; Limit for the Fibonacci sequence
VALUE: CONST  8               ; Value to be output
ZERO:  CONST  0               ; Constant for the initial Fibonacci number
ONE:   CONST  1               ; Constant for the second Fibonacci number
