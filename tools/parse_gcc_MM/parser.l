%{
// 定义全局变量区域
%}

%%
^.+\.o:.+$ {fprintf(yyout, "obj/%s", yytext);}
^.+$ {fprintf(yyout, "%s", yytext);}
%% 

#include <stdio.h>
int yywrap(void) {
    return 1;
}
int main(int argc, char** argv) {
    if (argc != 2)
        return -1;
    yyin = fopen("test", "r");
    yylex();
    fclose(yyin);
}
