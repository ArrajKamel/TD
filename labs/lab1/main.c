#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int symbol; 

void next_symbol() {
    symbol = yylex();
}

//parser functions 
int parseE();
int parseT();
int parseF();
int parseP();

// E → T '|' E | T
int parseE() {
    if(parseT()) {
        if(symbol == '|') {
            next_symbol();
            if(parseE()) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

int parseT() {
    if(parseF()) {
        if(parseT()) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}

int parseF() {
    if(parseP()) {
        if(symbol == '*') {
            next_symbol();
            return 1;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}
int parseP() {
    if(symbol == '(') {
        next_symbol();
        if(parseE()) {
            if(symbol == ')') {
                next_symbol();
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else if((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')) {
        next_symbol();
        return 1;
    } else {
        return 0;
    }
}


int main(){
    next_symbol();
    parseE();
}