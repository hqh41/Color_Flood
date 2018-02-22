/*6*6: vite
7*7: vite
8*8: pleusieurs seconds
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "ini_flood.h"

#define N 8

int times = 2*N;/*Amelioration 1: le stape minimal doit toujours inférieur à 2*N. ça doit être vérifié par mathématique*/

/*il y a 4 pointeurs sur 4 noeuds de chaque noeud precedent, parce que il y a 5 couleurs*/
struct noeud{
	int **a;
	struct noeud *f[4];
	int p;/*le profondeur*/
};

typedef struct noeud *ab;

ab node(int **x, struct noeud *b[4]){
	ab res = (ab)malloc(sizeof(struct noeud));
	res->a = x;
	int i;
	for(i = 0; i < 4; i++){
		(res->f)[i] = b[i];
	}
	res->p = 0;
	return res;
}

void affiche_matrix(int **a, int size){
	int i, j;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			printf("%d\t", *(*(a + i) + j));
		}
	printf("\n");
	}
}

void destroy_arbre(ab x)
{
	int i;
	for(i = 0; i < 4; i++) {
		if(x->f[i] != NULL)
			destroy_arbre(x->f[i]);
	}
	for(i = 0; i < N; i++)
		free(x->a[i]);
	free(x->a);
	free(x);
}

/*c signifie le couleur que on a applique le dernier fois, donc cette fois on ne peut pas appliquer c*/
void solveur(ab x, int c, int size){
	int i, j, k;
	int l = 0;
	for(i = 0; i < 5; i++){
		if(i != c){
			if((x->p) < times){
				if(une_couleur(x->a, size) != 1){
					int **b = malloc(size * sizeof(int *));
					for(j = 0; j < N; j++){
						b[j] = malloc(size * sizeof(int));
					}
					for(k = 0; k < N; k++){
						for(j = 0; j < N; j++){
							b[k][j] = (x->a)[k][j];
						}
					}
					propage(b, i, size);
					struct noeud *vide[4] = {NULL, NULL, NULL, NULL};
					ab y = node(b, vide);
					y->p = (x->p) + 1;
					(x->f)[l] = y;
					l++;
					solveur(y, i, size);
					if (times == y->p) break;
					/*Amelioration 3: seuelement break le node parents*/
				}
				else{
					if (x->p < times) 
						times = x->p;/*Amelioration 2: convergence*/
					printf("%d\n", x->p);
					return;/*return ou break? return. ça te dit aller a ligne 89 directement et ne effectue pas ligne 88 */
				}
			}
			else{
				return;
			}
		}
		else
			continue;
	}
}

int main(){
	int size = N;
	int i, j;
	int **a = malloc(size*sizeof(int *));
	for(j = 0; j < N; j++){
		a[j] = malloc(size*sizeof(int));
	}

	srand(time(NULL));
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			*(*(a + i) + j) = rand()%5;
		}
	}

	int b[8][8] = {
		{2,4,3,2,0,4,0,1},
		{3,2,4,4,1,0,0,3},
		{0,2,0,4,1,1,3,4},
		{2,4,4,3,3,1,3,2},
		{3,0,3,1,1,0,2,2},
		{2,1,3,1,3,4,1,2},
		{3,1,3,2,0,4,4,4},
		{2,4,1,0,3,1,3,3},
	};

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			*(*(a + i) + j) = b[i][j];
		}
	}

	// int b[6][6] = {
	// 	{1,3,1,0,0,3},
	// 	{2,0,1,1,2,3},
	// 	{3,1,3,4,4,0},
	// 	{3,3,3,4,3,1},
	// 	{3,2,4,2,1,0},
	// 	{2,0,2,0,4,4},
	// };

	// for(i = 0; i < N; i++){
	// 	for(j = 0; j < N; j++){
	// 		*(*(a + i) + j) = b[i][j];
	// 	}
	// }

	affiche_matrix(a, N);

	struct noeud *vide[4] = {NULL, NULL, NULL, NULL};
	ab x = node(a, vide);
	solveur(x, -1, N);
	destroy_arbre(x);
	return 0;
}

