%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex(void);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'

%token '(' ')'

%%
lines: /* empty */
     | lines line
;

line: '\n'
    | exp '\n' { printf("= %d\n", $1); }
;

exp: NUMBER
   | exp '+' exp { $$ = $1 + $3; }
   | exp '-' exp { $$ = $1 - $3; }
   | exp '*' exp { $$ = $1 * $3; }
   | exp '/' exp { $$ = $1 / $3; }
   | '(' exp ')' { $$ = $2; }  /* Handle parentheses */
   ;


%%
void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}

int main(void) {
  return yyparse();
}

