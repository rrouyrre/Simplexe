#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<time.h>
#include "fct.h"


//--------------------------------------------------------
//                       programme principal
//--------------------------------------------------------
int main()
{
	double **A2;
	double **A, *d, *cn, *cb;
	double *b;
	int indicel /*"indice ligne"*/, indicec /*"indice colonne"*/;
	int testPrimale, res2, testDuale, max, min, it, sumb;
	double coef,coef2,c,pivot;
	int n, m;
	
	// Initialisation de la matrice A :
	printf("nombre de lignes ? ");
	scanf("%d",&n);
	printf("nombre de colonnes ? ");
	scanf("%d",&m);
	A=NotreAlloc(n,m);
	init(A,n,m);
	
	// Allocation de la mémoire pour les vecteurs b, d, cn et cb :
	b=(double*)malloc((n-1)*sizeof(double));
	d=(double*)malloc(n*sizeof(double));
	cn=(double*)malloc(n*sizeof(double));
	cb=(double*)malloc((n-1)*sizeof(double));

	// Initilisation de b et cb :
	testPrimale = 1;
	for(int i=0; i<n-1; i++)
	{
		b[i] = A[i][m-1]; // Dernière colonne de la matrice A
		cb[i] = A[n-1][m-n+i];
		if(b[i]<0) // Ici B-1 = Id, mais normalement on vérifie si B-1*b est positif.
		{
			testPrimale = 0;
		}
		printf("cb[%d]=%f \n", i, cb[i]);
	}

	// Initialisation des vecteurs cn et d :
	testDuale = 1;
	for(int i=0; i<n;i++)
	{
		cn[i] = A[n-1][i]; // Les n premiers coefficients de la dernière ligne
		d[i] = cn[i]; // dn = cn -cb*(B-1)*N
		if(d[i]<0)
		{
			testDuale = 0;
		}
	}

	if(testPrimale==1)
	{
		printf("La base est primale réalisable. Le simplexe donne : \n");
		simplexe(A, n, m);
	}
	else
	{
		printf("La base n'est pas primale réalisable. \n");// Si b n'est pas positif alors res = 0 et la base n'est pas primale réalisable
		if(testDuale==1)
		{
			printf("La base est duale réalisable. Le dual donne : \n");
			dual(A, n, m);
		}
		else
		{
			printf("La base n'est pas duale réalisable. \n");
			A2 = NotreAlloc(n,m+n-1);
			A2 = calculA2(A, n, m, b);
			affichage(A2, n, m+n-1);
			printf("Le simplexe donne : \n");
			pasDual(A2, n, m, cn);
		}
	}
	
	return 0;
}
