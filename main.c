#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "chapter4_calculator.h"
#include "math.h"

//reverse polish calculator
int main(){
//    int type;
//    double op2;
    char s[100];
//
//    while((type = getop(s)) != EOF){
//        switch (type) {
//            case NUMBER:
//                push(atof(s));
//                break;
//            case NEGNUMBER:
//                push(-atof(s));
//                break;
//            case '+':
//                push(pop() + pop());
//                break;
//            case '*':
//                push(pop() * pop());
//                break;
//            case '-':
//                op2 = pop();
//                push(pop() - op2);
//                break;
//            //4-5 sin
//            case 's':
//                push(sin(pop()));
//                break;
//            //4-5 pow
//            case '^':
//                op2 = pop();
//                push(pow(pop(), op2));
//                break;
//            //4-5 exp
//            case 'e':
//                push(exp(pop()));
//                break;
//            case '/':
//                op2 = pop();
//                if(op2 != 0.0)
//                    push(pop() / op2);
//                else
//                    puts("error: division by 0");
//                break;
//            // 4-3 Add modulus support
//            case '%':
//                op2 = pop();
//                push((int)pop() % (int)op2);
//                break;
//            case '\n':
//                printf("\t%.8g\n", pop());
//                break;
//            case '\t':
//                op2 = pop();
//                push(pop() - op2);
//                printf("\t%.8g\n", pop());
//                break;
//            case 0:
//                break;
//            default:
//                printf("error: unkown command %s\n", s);
//                break;
//        }
//    }
//    return 0;
while(s[0] != EOF){
    checkLine(s);
}
}
