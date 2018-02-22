#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int une_couleur(int **a, int size){
	int i, j;
	int t = a[0][0];
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(a[i][j] != t)
				return -1;
		}
	}
	return 1;
}

void trouve(int **a, int x, int y, int c, int **b, int n)/*x0, y0 pour reserver le point on a deja trouve liant a cet point*/
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

void propage(int **a, int k, int size)
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
}

int ini_flood(int **a, int size){
	/*grille aleatoire*/
	int i, j, t;
	// srand(time(NULL));/*time comme graine de numbre aleatoire, on le mets dehors de for*/
	int qh[8][8] = {
		{2,4,3,2,0,4,0,1},
		{3,2,4,4,1,0,0,3},
		{0,2,0,4,1,1,3,4},
		{2,4,4,3,3,1,3,2},
		{3,0,3,1,1,0,2,2},
		{2,1,3,1,3,4,1,2},
		{3,1,3,2,0,4,4,4},
		{2,4,1,0,3,1,3,3}};
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			// t = rand()%5;
			a[i][j] = qh[i][j];
		}
	}
// int c[8][8] = {
// 		{1,1,2,1,4,4,0,0},
// 		{0,1,1,1,2,4,0,1},
// 		{1,1,2,1,3,3,1,3},
// 		{4,2,2,1,1,3,1,4},
// 		{4,2,2,1,1,2,2,3},
// 		{4,2,1,3,0,0,0,3},
// 		{4,2,3,1,0,0,2,0},
// 		{1,1,2,3,0,0,4,4},
// 	};
// 	for(i = 0; i < size; i++){
// 		for(j = 0; j < size; j++){
// 			a[i][j] = c[i][j];
// 		}
// 	}
	return 0;
}

void affiche_flood(int **a, int size, char c[6]){
	int i, j;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			printf("%c", c[a[i][j]]);
		}
		printf("\n");
	}
}

// int main(){
// 	char c[6] = {'B', 'V', 'R', 'J', 'M', 'G'};
// 	int size, i, k;
// 	int step = 0;
// 	printf("the size of flood you want?");
// 	scanf("%d", &size);
// 	int **a = malloc(size * sizeof(int *));
// 	for(i = 0; i < size; i++){
// 		a[i] = malloc(size * sizeof(int));
// 	}
// 	ini_flood(a, size);
// 	affiche_flood(a, size, c);
// 	while(une_couleur(a, size) != 1){
// 		printf("the index of color you want to choose?");
// 		scanf("%d", &k);
// 		propage(a, k, size);
// 		affiche_flood(a, size, c);
// 		step++;
// 	}
// 	printf("step: %d\n", step);
// 	for(i = 0; i < size; i++){
// 		free(a[i]);
// 	}
// 	return 0;
// }
