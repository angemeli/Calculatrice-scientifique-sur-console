#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>

#include "../header/analyse.h"
#include "../header/gestion_chaines.h"

using namespace std;

double analyse_expression(char *expression, int &i);
double analyse_term(char *expression, int &i);
double analyse_factor(char *expression, int &i);
double analyse_number(char *expression, int &i);
double analyse_function(char *expression, int &i);


double analyse_number(char *expression, int &i) {
    char *number = (char *)malloc(1);
    int n = 0;
    i = 0;
    while (*expression != '\0' && ((*expression >= '0' && *expression <= '9') || *expression == '.')) {
        number = (char *)realloc(number, n+2);
        number[n] = *expression;
        n+=1;
        expression += 1;
        i += 1;
    }
    number[n] = '\0';

    double value = stod(number);
    return value;
}

double analyse_function(char *expression, int &i) {
    i = 0;
    char *function = (char *)malloc(1);
    int j = 0;

    while (*expression == ' ') {
        expression += 1;
    }

    while (isalpha(*expression)) {
        function = (char *)realloc(function, j+2);
        function[j] = *expression;
        j += 1;
        expression += 1;
        i += 1;
    }
    function[j] = '\0';

    if (*expression == '(') {
        expression += 1;
        i+=1;
        int k = i;
        double arg = analyse_expression(expression, i);
        i += k+1;
        if (comparaison_chaines(function, "sqrt") == 0) {
            return sqrt(arg);
        }
        else if (comparaison_chaines(function, "sin") == 0) {
            arg = (M_PI*arg)/180;
            return sin(arg);
        }
        else if (comparaison_chaines(function, "cos") == 0) {
            arg = (M_PI*arg)/180;
            return cos(arg);
        }
        else if (comparaison_chaines(function, "tan") == 0) {
            arg = (M_PI*arg)/180;
            return tan(arg);
        }
        else if (comparaison_chaines(function, "ln") == 0) {
            return log(arg);
        }
        else if (comparaison_chaines(function, "exp") == 0) {
            return exp(arg);
        }
    }

    cerr << "Erreur : fonction non reconnue ou mauvaise syntaxe : " << function << "\n";
    free(function);
    exit(EXIT_FAILURE);
}

double analyse_factor(char *expression, int &i) {
    i = 0;
    while (*expression == ' ') {
        expression += 1;
    }

    if ((*expression >= '0' && *expression <= '9') || *expression == '.') {
        return analyse_number(expression, i);
    } 
    else if (isalpha(*expression)) {
        return analyse_function(expression, i);
    }

    else if (*expression == '(') {
        expression += 1;
        double result = analyse_expression(expression, i);
        if (*expression == ')') {
            return result;
        } 
        else {
            cerr << "Erreur : parenthese fermante manquante" << endl;
            exit(EXIT_FAILURE);
        }
    } 

    cerr << "Erreur : caractere non reconnu" << endl;
    exit(EXIT_FAILURE);
}

double analyse_term(char *expression, int &i) {
    i = 0;
    while (*expression == ' ') {
        expression += 1;
    }
    double result = analyse_factor(expression, i);
    //cout << result <<"\n";
    return result;
}

double analyse_expression(char *expression, int &i) {
    i = 0;
    double result = analyse_term(expression, i);
    expression += i;

    while (*expression != '\0') {
        while (*expression == ' ') {
            expression += 1;
        }
        char op = *expression;

        if (op == '+' || op == '-') {
            expression += 1;
            while (*expression == ' ') {
                expression += 1;
            }
            double next_term = analyse_term(expression, i);
            if (op == '+') {
                result += next_term;
                expression += i;
            } 
            else {
                result -= next_term;
                expression += i;
            }
        }

        else if (op == '*' || op == '/') {
            expression += 1;
            while (*expression == ' ') {
                expression += 1;
            }
            double next_factor = analyse_term(expression, i);
            if (op == '*') {
                result *= next_factor;
                expression += i;
            } 
            else {
                result /= next_factor;
                expression += i;
            }
        } 

        else {
            break;
        }
    }

    return result;
}
