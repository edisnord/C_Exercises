//
// Created by edis on 22-05-29.
//

#include "chapter4_calculator.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "math.h"

char buf[100];
int bufp;
int sp;
double val[100];

//4-8 Not more than one character of pushback
int getch() {
    return (bufp == 1) ? buf[bufp--] : getchar();
}

//4-9 Handle EOF
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        puts("ungetch: too many characters!");
    else if (c == EOF) {
        puts("ungetch: EOF detected, exiting...");
        exit(EOF);
    } else
        buf[bufp++] = c;
}

//4-10 use getline()
int checkLine(char s[]) {
    double returned;
    double op2;
    int operator;
    size_t buflen = 100 * sizeof(char);
    char *tok;
    getline(&s, &buflen, stdin);
    char *tmp = malloc(buflen * sizeof(char));
    strcpy(tmp, s);
    for (tok = strtok(tmp, " "); tok && *tok; tok = strtok(NULL, " \n")) {
        if ((operator = getop(tok, &returned))) {
            switch (operator) {
                case 0:
                    push(returned);
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '\\':
                    puts("unknown input\n");
                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        puts("error: division by 0");
                    break;
                    // 4-3 Add modulus support
                case '%':
                    op2 = pop();
                    push((int) pop() % (int) op2);
                    break;
                    // 4-5 sin
                case '\'':
                    push(sin(returned));
                 break;
                 //4-5 pow
                case '^':
                    op2 = pop();
                    push(pow(pop(), op2));
                    break;
                    //4-5 exp
                case '\t':
                    push(exp(returned));
                    break;
            }
        } else {
            //number returned
            push(returned);
        }
    }
    printf("%.8g\n", pop());
}

int getop(char s[], double *parsed) {
    char *error;
    int flag = 1;
    if (s[0] == '-' && isdigit(s[1])) {
        flag *= -1;
        *parsed = strtod(&s[1], &error) * flag;
        return (error[0] == '\0') ? 0 : '\\';
    } else if (s[0] == '-' && !isdigit(s[1])) {
        return '-';
    }
    if (isdigit(s[0])) {
        *parsed = strtod(s, &error);
        return (error[0] == '\0') ? 0 : '\\';
    } else {
        if (strstr(s, "sin") != NULL){
            *parsed = strtod(s, &error);
            return '\'';
        }
        else if (strstr(s, "exp") != NULL){
            *parsed = strtod(s, &error);
            return '\t';
        }
        else return s[0];
    }
}

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop() {
    if (sp > 0)
        return val[--sp];
    else {
        puts("error: stack empty\n");
        return 0.0;
    }
}

//4-4 clear stack
void clearStack() {
    sp = 0;
    puts("stack has been cleared");
}

//4-4 Swap top elements
void swap() {
    if (sp > 0) {
        double temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
        puts("Top elements swapped");
    } else {
        puts("error: stack empty\n");
    }
}

//4-4 duplicate top element
void dupeTop() {
    if (sp > 0) {
        double addition = val[sp - 1];
        val[sp++] = addition;
        puts("Top element duplicate top element");
    } else {
        puts("error: stack empty\n");
    }
}

//4-4 print top element without removing
void peek() {
    if (sp > 0)
        printf("Top element: %g", val[sp - 1]);
    else {
        puts("error: stack empty\n");
    }
}