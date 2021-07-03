#ifndef CALCULATOR_H
#define CALCULATOR_H

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Spring 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>
#include "stack.h"


Stack<double> opr; // stack for operands
Stack<char> opt;   // stack for operators


//
// Modify Eval() below to evaluate the given expression
//
int priority(char c){
    if(c == '*' || c == '/'){
        return 1;
    }else if(c == '+' || c == '-'){
        return 0;
    }else{
        return -1;
    }
}

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

bool isOperand(char c){
    return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' ||
    c == '6' || c == '7' || c == '8' || c == '9' || c == '.';
}

double Calculate(char c, double x, double y){
    double ans = 0;
    switch(c){
        case '+': ans = x + y; break;
        case '-': ans = x - y; break;
        case '*': ans = x * y; break;
        case '/': ans = x / y; break;
    }
    return ans;
}

double Eval(char* in)
{
    double out = 0;
    char buf[1000]; // temp buffer
    
    double operand;
    int i = 0, bi = 0;
        
    while(in[i] != '\0')
    {
        char c = in[i];
        bool flag = 0;
        
        if(isOperand(c))
        {
            if(i >= 2 && in[i-1] == '-' && in[i-2] == '('){
                flag = 1;
            }
            while(in[i] != '\0' && isOperand(in[i])){
                buf[bi++] = in[i++];
            }
            buf[bi] = '\0';
            operand = atof(buf);
            bi = 0;
            
            if(flag){
                flag = 0;
                opr.Push(-operand);
            }else{
                opr.Push(operand);
            }
           
        }else if(isOperator(c)){
            if(c == '-' && in[i-1] == '('){
                i++; continue;
            }else if(c == '('){
                opt.Push(c);
            }else if(c == ')'){
                while(opt.Top()!= '('){
                    char temp = opt.Top(); opt.Pop();
                    double y = opr.Top(); opr.Pop();
                    double x = opr.Top(); opr.Pop();
                    double num = Calculate(temp, x, y);
                    opr.Push(num);
                }
                opt.Pop();
            }else
            {
                while(!opt.IsEmpty() && priority(c) <= priority(opt.Top())){
                    char temp = opt.Top(); opt.Pop();
                    double y = opr.Top(); opr.Pop();
                    double x = opr.Top(); opr.Pop();
                    double num = Calculate(temp, x, y);
                    opr.Push(num);
                }
                opt.Push(c);
            }
            i++;
        }else{
            i++;
            continue;
        }
    }
    
    while(!opt.IsEmpty()){
        char temp = opt.Top(); opt.Pop();
        double y = opr.Top(); opr.Pop();
        double x = opr.Top(); opr.Pop();
        double num = Calculate(temp, x, y);
        opr.Push(num);
    }
    
    out = opr.Top();
    opr.Pop();
    return out;
}
#endif

