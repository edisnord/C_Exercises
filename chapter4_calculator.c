//
// Created by edis on 22-05-29.
//

#include "chapter4_calculator.h"

char buf[100];
int bufp;
int sp;
double val[100];

int getch(){
    return (bufp>0) ? buf[bufp--] : getchar();
}

void ungetch(int c){
    if(bufp >= BUFSIZE)
        puts("ungetch: too many characters!");
    else
        buf[bufp++] = c;
}

int getop(char s[]){
    int i,c,flag;
    flag = 0;
    while((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    //4-3 Handle negative numbers
    if(!isdigit(c) && c  != '.') {
        if(c == '-' && isdigit(flag = getch())){
            s[0] = flag;
            flag = 1;
        } else if (c == '-'){
            if(flag == '\n') return '\t';
            else if(flag == '\0') return '-';
            flag = 0;
        }
        if(!flag)
            return c;
    }
    i = 0 + flag;
    if(isdigit(c))
        while (isdigit(s[++i] = c = getch()));
    if(c == '.')
        while(isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if(c != EOF)
        ungetch(c);
    if(!flag)
        return NUMBER;
    else
        return NEGNUMBER;
}

void push(double f){
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(){
    if(sp > 0)
        return val[--sp];
    else {
        puts("error: stack empty\n");
        return 0.0;
    }
}

//4-4 clear stack
void clearStack(){
    sp = 0;
    puts("stack has been cleared");
}

//4-4 Swap top elements
void swap(){
    if(sp > 0){
        double temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
        puts("Top elements swapped");
    }
    else {
        puts("error: stack empty\n");
    }
}

//4-4 duplicate top element
void dupeTop(){
    if(sp > 0){
        double addition = val[sp - 1];
        val[sp++] = addition;
        puts("Top element duplicate top element");
    }
    else {
        puts("error: stack empty\n");
    }
}

//4-4 print top element without removing
void peek(){
    if(sp > 0)
        printf("Top element: %g", val[sp - 1]);
    else {
        puts("error: stack empty\n");
    }
}