#include <iostream>
#include <cstdlib>

#include "header/analyse.h"

using namespace std;

int main(int argc, char const *argv[]) {
    char expression[500];

    cout << "\nEntrez une expression : ";
    cin.getline(expression, 500);

    char *ptr_expression = expression;
    int i = 0;

    double result = analyse_expression(ptr_expression, i);
    cout << "\nLe resultat est : " << result << "\n";

    return 0;
}