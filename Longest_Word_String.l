%{
#include <stdio.h>
#include <string.h>

int longestLength = 0;
char longestWord[100];
%}

%%
[a-zA-Z]+ {
  if (yyleng > longestLength) {
    longestLength = yyleng;
    strcpy(longestWord, yytext);
  }
}

. ; /* Ignore all other characters */

%%

int main() {
  yylex();
  printf("Longest word: %s\nLength: %d\n", longestWord, longestLength);
  return 0;
}
