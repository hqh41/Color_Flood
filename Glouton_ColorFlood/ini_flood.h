#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "glouton.h"

int une_couleur(int **a, int size){
	int i, j;
	int t = a[0][0];
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(a[i][j] != t)
				return 0;
		}
	}
	return 1;
}

void trouve(int **a, int x, int y, int c, int **b, int n)
{
	int p[3][2];
	int l = 0;
	if(y < (n-1) && a[x][y+1] == c && (b[x][y+1] != 1)) {
		p[l][0] = x;
		p[l][1] = y+1;
		b[x][y+1] = 1;
		l++;
	}
	if (x < (n-1) && a[x+1][y] == c && (b[x+1][y] != 1)) {
		p[l][0] = x+1;
		p[l][1] = y;
		b[x+1][y] = 1;
		l++;
	}
	if (x > 0 && a[x-1][y] == c && (b[x-1][y] != 1)) {
		p[l][0] = x-1;
		p[l][1] = y;
		b[x-1][y] = 1;
		l++;
	}
	if (y > 0 && a[x][y-1] == c && (b[x][y-1] != 1)) {
		p[l][0] = x;
		p[l][1] = y-1;
		b[x][y-1] = 1;
		l++;
	}
	if (l == 0)
		return;
	else {
		int i;
		for (i=0;i<l;i++) {
			trouve(a, p[i][0], p[i][1], c, b, n);
		}
	}
}

/*void propage(int **a, int k, int size)
{
	int i, j;
	int **b = malloc(size * sizeof(int*));
	for(i = 0; i < size; i++){
		b[i] = malloc(size * sizeof(int));
	}
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			b[i][j] = 0;
	b[0][0] = 1;
	trouve(a, 0, 0, a[0][0], b, size);
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++) {
			if (b[i][j] == 1)
				a[i][j] = k;
		}
	}
	for(i = 0; i < size; i++){
		free(b[i]);
	}
}*/

void propage(int **a, int size)
{
	int colorIndex;
	int i, j;
	int **b = malloc(size * sizeof(int*));
	for(i = 0; i < size; i++){
		b[i] = malloc(size * sizeof(int));
	}
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			b[i][j] = 0;
	b[0][0] = 1;
	trouve(a, 0, 0, a[0][0], b, size);
	colorIndex = max_color_borne_collect(a, b, size);
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++) {
			if (b[i][j] == 1)
				a[i][j] = colorIndex;
		}
	}
	for(i = 0; i < size; i++){
		free(b[i]);
	}
}

int ini_flood(int **a, int size){
	int i, j, t;
	int qh[6][6] = {
			{0, 1, 1, 2, 3, 4},
			{4, 3, 4, 0, 1, 4},
			{3, 2, 2, 1, 3, 0},
			{3, 4, 2, 0, 2, 1},
			{0, 3, 2, 1, 1, 0},
			{0, 0, 1, 4, 0, 0}};
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			t = rand()%5;
			a[i][j] = qh[i][j];
		}
	}
	return 0;
}

void affiche_flood(int **a, int size){
	int i, j;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			printf("%d", a[i][j]);
		}
		printf("\n");
	}
	printf("-----------\n");
}
