#include "polynomial.h"
#include <iostream>
#include <math.h>


//
// Implementation
//

// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
    capacity = source.capacity;
    terms = source.terms;
    termArray = new Term[capacity];
    for(int i = 0; i < terms; i++){
        termArray[i].coef = source.termArray[i].coef;
        termArray[i].exp = source.termArray[i].exp;
    }
}

// Destructor
Polynomial::~Polynomial()
{
    delete [] termArray;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
    if(this == &source){
        return *this;
    }else{
        delete[] termArray;
        capacity = source.capacity;
        terms = source.terms;
        termArray = new Term[capacity];
        for(int i = 0; i < terms; i++){
            termArray[i].coef = source.termArray[i].coef;
            termArray[i].exp = source.termArray[i].exp;
        }
    }
    return *this;
}



// Sum of *this and source polynomials
Polynomial Polynomial::operator +(const Polynomial& source)
{
    Polynomial c;
    float temp;
    
    int a = 0, b = 0;
    int a_finish = terms, b_finish = source.terms;

    while((a < a_finish) && (b < b_finish)){
        int comp = (termArray[a].exp > source.termArray[b].exp)? 1
        :(termArray[a].exp == source.termArray[b].exp)? 0 : -1;
        switch(comp){
            case -1:
                c.CreateTerm(source.termArray[b].coef, source.termArray[b].exp);
                b++; break;
            case 0:
                temp = termArray[a].coef + source.termArray[b].coef;
                if(temp) c.CreateTerm(temp, source.termArray[b].exp);
                a++; b++; break;
            case 1:
                c.CreateTerm(termArray[a].coef,termArray[a].exp);
                a++; break;
        }
    }

    for(; a< a_finish; a++){
        c.CreateTerm(termArray[a].coef, termArray[a].exp);
    }
    for(; b< b_finish; b++){
        c.CreateTerm(source.termArray[b].coef, source.termArray[b].exp);
    }
    return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
    Polynomial c;
    float temp;

    int a = 0, b = 0;
    int a_finish = terms, b_finish = source.terms;

    while((a < a_finish) && (b < b_finish)){
        int comp = (termArray[a].exp > source.termArray[b].exp)? 1
        :(termArray[a].exp == source.termArray[b].exp)? 0 : -1;
        switch(comp){
            case -1:
                c.CreateTerm(-source.termArray[b].coef, source.termArray[b].exp);
                b++; break;
            
            case 0:
                temp = termArray[a].coef - source.termArray[b].coef;
                if(temp) c.CreateTerm(temp, termArray[a].exp);
                a++; b++; break;
            
            case 1:
                c.CreateTerm(termArray[a].coef, termArray[a].exp);
                a++; break;
        }
    }

    for(; a< a_finish; a++){
        c.CreateTerm(termArray[a].coef, termArray[a].exp);
    }
    for(; b< b_finish; b++){
        c.CreateTerm(-source.termArray[b].coef, source.termArray[b].exp);
    }
    return c;
}


Polynomial Polynomial::operator * (const Polynomial& source)
{
    Polynomial c;
    
    for(int i = 0; i < terms; i++){
        for(int j = 0; j < source.terms; j++){
            float new_coef = termArray[i].coef * source.termArray[j].coef;
            int new_exp = termArray[i].exp + source.termArray[j].exp;
            Polynomial d;
            d.CreateTerm(new_coef, new_exp);
            c = c + d;
        }
    }
    
    return c;
}


float Polynomial::Eval(float x)
{
    float ret = 0;
    
    for(int i = 0; i < terms; i++){
        float temp = pow(x, termArray[i].exp);
        ret +=  temp * termArray[i].coef;
    }
    return ret;
}



// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
    Polynomial c;
    c.terms = 0;
    
    for(int i = 0; i < terms; i++){
        if(termArray[i].exp == 0) break;
        c.termArray[i].coef = termArray[i].coef * termArray[i].exp;
        c.termArray[i].exp = termArray[i].exp - 1;
        c.terms++;
    }
    return c;
}


void Polynomial::CreateTerm(const float coef, const int exp)
{
    /* 1. Create a new term. If the term exists, overwrite its coefficient.
    2. No term existing in the current polynomial of a given exponent -> create a new term
    3. array arranged in descending order
    4. zero coefficient -> remove the term
    */
    
    // in operator +/- already avoid the situation when coef == 0
    if(!coef){
        return;
    }
    
    int temp = -1;
    
    int left = 0, right = terms - 1;
    while(left <= right){
        int mid = left + (right - left)/ 2;
        if(termArray[mid].exp == exp){
            temp = mid;
            termArray[mid].coef = coef; // overwrite
            return;
        }
        if(termArray[mid].exp > exp){
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    
    int insert = left;
    
    terms++;
    if(terms >= capacity){
        capacity *= 2;
        Term * temp = new Term[capacity];
        for(int i = 0; i < terms; i++){
            temp[i].coef = termArray[i].coef;
            temp[i].exp = termArray[i].exp;
        }
        delete[] termArray;
        termArray = temp;
    }
    
    int j = terms;
    for(; j > insert; j--){
        termArray[j].exp = termArray[j-1].exp;
        termArray[j].coef = termArray[j-1].coef;
    }
    
    termArray[insert].exp = exp;
    termArray[insert].coef = coef;
    
    return;
}


