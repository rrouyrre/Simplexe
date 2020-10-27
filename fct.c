#include <stdio.h>
#include <stdlib.h>


//--------------------------------------------------------
//                      Fonction NotreAlloc
//--------------------------------------------------------

// Permet d'allouer de la mémoire à une matrice

double** NotreAlloc(int n,int m) 
{
	int i;
	double *vect,**mat;

	vect = (double*)malloc((n*m)*sizeof(double));
	mat = (double**)malloc(n*sizeof(double*));

	for(i=0;i<n;i++)
		{
		mat[i]=vect;
		vect+=m;
		}

	return(mat);
}


//--------------------------------------------------------
//			Initialisation
//--------------------------------------------------------

// Demande à l'utilisateur d'initialiser la matrice A de taille n*m

void init(double **A, int n, int m)
{
	for(int i=0; i<n; i++) // Parcourre les lignes
	{
		for(int j=0; j<m; j++) // Parcourre les colonnes
		{
			printf("A[%d][%d] : ",i+1 ,j+1);
			scanf("%lf",&A[i][j]);
		}
		printf("\n");
	}
}


//--------------------------------------------------------
//			Affichage
//--------------------------------------------------------

// Permet d'afficher la matrice A de taille n*m

void affichage(double **A, int n, int m)
{
	for(int i=0; i<n; i++) // Parcourre les lignes
	{
		for(int j=0; j<m; j++) // Parcourre les colonnes
		{
			printf(" %.2f ",A[i][j]); // Affiche les coefficients
		}
		printf("\n"); // Revient à la ligne à la fin de chaque ligne
	}
	printf("\n");
}


//---------------------------------------------------------
//			Simplexe
//---------------------------------------------------------

void simplexe(double **A, int n, int m)
{
	int res, max, indicec, min, indicel;
	double pivot, c, coef, coef2;

	res=0;
	int it = 0;
	while((res == 0) && (it<2)) // Conditions d'arrêt : si le simplexe est fini ou si le programme fait trop d'itérations
	{
		// Recherche de l'indice de la colonne de la case maximale de la dernière ligne :
		max = 0;
		for(int j=0;j<m;j++)
		{
			if (A[n-1][j]<max)
			{
				max = A[n-1][j];
				indicec = j;
			}
		}
		printf( "indicec : %d \n",indicec);
		
		// Recherche de l'indice de la ligne de la case dont le rapport entre la case de la dernière colonne et celle-ci est minimal :
		min = 10000000;
		for(int i=0;i<n-1;i++)
		{
			coef = A[i][m-1];
			coef2 = A[i][indicec];
			if ((coef/coef2 > 0 ) && (coef/coef2)<min)
			{
				min = coef/coef2;
				indicel = i;
			}
		}
		
		printf("indicel : %d \n",indicel );
		printf("%f \n", A[indicel][indicec]);

		// On divise toutes les cases de la ligne choisie par le pivot :
		pivot = A[indicel][indicec];
		for(int j=0; j<m; j++)
		{
			A[indicel][j] = A[indicel][j]/pivot;
		}

		// On applique le pivot de Gauss pour rendre toutes les cases de la colonne égales à 0 :
		for(int i=0; i<n; i++)
		{
			if (i!=indicel)
			{
				c = A[i][indicec];
				for(int j=0; j<m; j++)
				{
					A[i][j] -= c*A[indicel][j];
				}
			}
		}

		// On teste si tous les coefficients de la dernière ligne sont positifs pour savoir si le simplexe est fini :
		res = 1;
		for(int j=0;j<m;j++)
		{
			if (A[n-1][j] < 0)
			{ 
				res = 0;
			}
		}
		it++;
	}
	affichage(A,n,m);
}


//--------------------------------------------------------
//			Dual
//--------------------------------------------------------

void dual(double **A, int n, int m)
{
	int indicel /*"indice ligne"*/, indicec /*"indice colonne"*/;
	int res2, max, min, it;
	double coef,coef2,c,pivot;

	res2 = 0;
	it = 0;
	while((res2 == 0) && (it<2))
	{
		// Recherche de l'indice de la ligne de la case maximale de la dernière colonne :
		max = 0;
		for(int i=0;i<n-1;i++)
		{
			if (A[i][m-1]<max)
			{
				max = A[i][m-1];
				indicel = i;
			}
		}
		
		// Recherche de l'indice de la colonne de la case dont le rapport entre la case de la dernière ligne et celle-ci est minimal :
		min = 10000000;
		for(int j=0;j<n-1;j++)
		{
			coef = A[n-1][j];
			coef2 = A[indicel][j];
			if ((coef/coef2 < 0 ) && abs(coef/coef2)<min)
			{
				min = coef/coef2;
				indicec = j;
			}
		}
		
		pivot = A[indicel][indicec];
		// On divise toutes les cases de la ligne choisie par le pivot :
		for(int j=0; j<m; j++)
		{
			A[indicel][j] = A[indicel][j]/pivot;
		}
		
		// On applique le pivot de Gauss pour rendre toutes les cases de la colonne égales à 0 :
		for(int i=0; i<n; i++)
		{
			if (i!=indicel)
			{
				c = A[i][indicec];
				for(int j=0; j<m; j++)
				{
					A[i][j] -= c*A[indicel][j];
				}
			}
		}
		
		res2 = 1;	
		// On teste si tous les coefficients de la dernière colonne sont positifs pour savoir si le simplexe est fini :
		for(int i=0;i<n-1;i++)
		{
			if (A[i][m-1] < 0)
			{ 
				res2 = 0;
			}
		}
		it++;
	}
	affichage(A, n, m);
}


//--------------------------------------------------------
//			PasDual
//--------------------------------------------------------

void pasDual(double **A, int n, int m, double *cn)
{
	int res, res2, max, indicec, indicel, min, it, diff, add, temp;
	double coef,coef2,c,pivot;

	res=0;
	it = 0;
	diff = m - n;
	add = m+n;
	while((res == 0) && (it<3))
	{
		max = 0;
		for(int j=0;j<add-2;j++)
		{
			if (A[n-1][j]<max)
			{
				max = A[n-1][j];
				indicec = j;
			}
		}
		
		min = 10000000;
		for(int i=0;i<n-1;i++)
		{
			coef = A[i][add-2];
			coef2 = A[i][indicec];
			if ((coef/coef2 > 0 ) && (coef/coef2)<min)
			{
				min = coef/coef2;
				indicel = i;
			}
		}
		
		pivot = A[indicel][indicec];
		for(int j=0; j<add-1; j++)
		{
			A[indicel][j] = A[indicel][j]/pivot;
		}		

		for(int i=0; i<n; i++)
		{
			if (i!=indicel)
			{
				c = A[i][indicec];
				for(int j=0; j<add-1; j++)
				{
					A[i][j] -= c*A[indicel][j];
				}
			}
		}
		
		res = 1;
		for(int i=0;i<add-1;i++)
		{
			if (A[n-1][i] < 0)
			{ 
				res = 0;
			}
		}
		it++;
	}

	affichage(A, n, add-1);
	
	double **A2;

	A2=NotreAlloc(n,m);

	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<m-1;j++)
		{
			A2[i][j] = A[i][j];
		}
	}
	
	for(int i=0; i<n-1; i++)
	{
		A2[i][m-1] = A[i][add-2];
	}
	
	for(int j=0; j<diff; j++)
	{
		A2[n-1][j] = 0;
	}

// A revoir :
	temp = 0;
	for(int j=0; j<n-1; j++)
	{
		temp = j + diff;
		for(int i=0; i<diff; i++)
		{
			A2[n-1][temp] = A2[n-1][temp]-cn[i]*A2[i][temp];
			printf("A2[%d][%d] : %.2lf, cn[%d] : %.2lf \n", n-1, temp, A2[n-1][temp], i, cn[i]);
		}
		//printf("%lf %lf %lf %lf %lf \n", A2[n-1][j+(m-n)], cn[0], A2[0][j], cn[1], A2[1][j]);
	}
	
	//A2[n-1][m-1] = -cn[0]*A2[0][m-1] -cn[1]*A2[1][m-1];
	
	affichage(A2, n, m);

	simplexe(A2, n, m);
}


//--------------------------------------------------------
//			Calcul de A2
//--------------------------------------------------------

double** calculA2(double **A, int n, int m, double *b)
{
	double **A2, *sum;
	int sumb;

	sum=(double*)malloc((m-1)*sizeof(double));
	
	for(int j=0; j<m-1; j++)
	{
		sum[j] = 0;
	}

	sumb = 0;
	{
		A2=NotreAlloc(n,m+n-1);
		for(int i=0; i<n-1; i++)
		{
			for(int j=0; j<m-1; j++)
			{
				A2[i][j] = A[i][j];
			}
			for(int j=m-1; j<m+n-2; j++)
			{
				if(j==i+m-1)
				{
					A2[i][j] = 1;
				}
				else
				{
					A2[i][j] = 0;
				}
			} 
			A2[i][m+n-2] = A[i][m-1];
		}

		for(int i=0; i<n-1; i++)
		{
			if(b[i]<0)
			{
				b[i] = -b[i];
				for(int j=0; j<m-1; j++)
				{ 
					A2[i][j] = -A2[i][j];
				}
				A2[i][m+n-2] = -A2[i][m+n-2];
			}
			sumb += b[i];
		}
		A2[n-1][m+n-2] = -sumb; // Remplissage de la dernière case

		// Remplissage de la dernière ligne :
		for(int j=0; j<m-1; j++)
		{	
			for(int i=0; i<n-1; i++)
			{
				sum[j] += A2[i][j];
			}
			A2[n-1][j] = -sum[j];
		}
	}
	
	return A2;
}










		

