%{
#include "calc.tab.h"
void yyerror(const char *s);
%}

%%
[ \t]+    ;  /* Ignore whitespace. */
[0-9]+    { yylval = atoi(yytext); return NUMBER; }
\n        { return '\n'; }
[+\-*/]   { return yytext[0]; }
"("       { return '('; }
")"       { return ')'; }
.         { yyerror("Unknown character"); }

%%

int yywrap(void) {
  return 1;
}
