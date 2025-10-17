#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "types.h"

int yylval;
int yylex();

int symbol; // current token
void nextsymbol(){
    symbol = yylex();
}

nodeType *con(int value) ;
nodeType *opr(int oper, int nops, ...) ;
void yyerror(char *s) ;

void ex(nodeType *p);

nodeType *Z();
nodeType *E();
nodeType *T();

void main(){
    nextsymbol();
    ex(Z());
}

// Z ::= E
nodeType *Z(){
    return E();
}

nodeType *E(){
    printf("Entering E with symbol: %d\n", symbol);
    nodeType *left = T();
    printf("After T in E, symbol: %d\n", symbol);
    while (symbol == '+')
    {
        nextsymbol();
        printf("After + in E, symbol: %d\n", symbol);
        nodeType *right = T();
        left = opr('+', 2, left, right);
    }
    return left;
}

nodeType *T(){
    printf("Entering T with symbol: %d\n", symbol);
    if(symbol == 256){
        nodeType *p = con(yylval);
        nextsymbol();
        return p;
    }
    else if(symbol == '('){
        nextsymbol();
        nodeType *p = E();
        if(symbol != ')'){
            yyerror("you forgot the )");
            exit(1);    
        }
        nextsymbol();
        return p;
    }
    else {
        yyerror("syntax error");
        exit(1);
    }
}

nodeType *con(int value) 
{ 
  nodeType *p; 
  
  /* allocate node */ 
  if ((p = malloc(sizeof(conNodeType))) == NULL) 
    yyerror("out of memory"); 
  /* copy information */ 
  p->type = typeCon; 
  p->con.value = value; 
  return p; 
} 

nodeType *opr(int oper, int nops, ...) 
{ 
  va_list ap; 
  nodeType *p; 
  size_t size; 
  int i; 

  /* allocate node */ 
  size = sizeof(oprNodeType) + (nops - 1) * sizeof(nodeType*); 
  if ((p = malloc(size)) == NULL) 
    yyerror("out of memory"); 
  /* copy information */
  p->type = typeOpr; 
  p->opr.oper = oper; 
  p->opr.nops = nops; 
  va_start(ap, nops); 
  for (i = 0; i < nops; i++) 
    p->opr.op[i] = va_arg(ap, nodeType*); 
  va_end(ap); 
  
  return p; 
}

void yyerror(char *s) 
{ 
  fprintf(stdout, "%s\n", s); 
} 