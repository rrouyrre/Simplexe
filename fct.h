#ifndef FCT_H_INCLUDED
#define FCT_H_INCLUDED
#include "fct.c"

/* Affichage plateau*/
double** NotreAlloc(int n, int m);
void init(double **A, int n, int m);
void affichage(double **A, int n, int m);
void simplexe(double **A, int n, int m);
void dual(double **A, int n, int m);
void pasDual(double **A, int n, int m, double *cn);
double** calculA2(double **A, int n, int m, double *b);

#endif // FCT_H_INCLUDED
