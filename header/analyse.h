#ifndef ANALYSE_H
#define ANALYSE_H

double analyse_expression(char *expression, int &i);
double analyse_term(char *expression, int &i);
double analyse_factor(char *expression, int &i);
double analyse_number(char *expression, int &i);
double analyse_function(char *expression, int &i);

#endif // ANALYSE_H