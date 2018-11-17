#include "ini_flood.h"

int main(){
	int j;
	int **a = malloc(N*sizeof(int *));
	for(j = 0; j < N; j++){
		a[j] = malloc(N*sizeof(int));
	}

	ini_flood(a, N);
	affiche_flood(a, N);

	/*while(!une_couleur(a, N)){
		scanf("%d", &c);
		propage(a, c, N);
		affiche_flood(a, N);
	}*/

	while(!une_couleur(a, N)){
		propage(a, N);
		affiche_flood(a, N);
	}

	return 0;
}