#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6
//选取格子数最多的颜色并返回
int max_color(int* c, int size){
    int colorIndex = 0;
    int max = c[0];
    for(int i = 0; i < 5; ++i){
        if(c[i] > max){
            max = c[i];
            colorIndex = i;
        }
    }
    return colorIndex;
}

//统计出边界相邻的各种颜色格子的个数
void voisin0(int *c, int **a, int **b, int i, int j, int size){
    if(i == 0 && b[i][j] == 0 && (b[i][j-1] == 1 || b[i][j+1] == 1 || (j <(size-1) && b[i+1][j] == 1))){
        ++c[a[i][j]];
        int p = a[i][j];
        return;
    }
    if(j == 0 && b[i][j] == 0 && (b[i-1][j] == 1 || (i <(size-1) && b[i+1][j] == 1) || b[i][j+1] == 1)){
        ++c[a[i][j]];
        int p = a[i][j];
        return;
    }
    if(i > 0 && j > 0 && b[i][j] == 0 && (b[i-1][j] == 1 || (i <(size-1) && b[i+1][j] == 1) || b[i][j-1] == 1 || (j < (size-1) && b[i][j+1] == 1))){
        ++c[a[i][j]];
        int p = a[i][j];
        return;
    }
    return;
}

//该格子在b中本身值为0，上下左右遍历后至少与一个1相邻
int max_color_borne_collect(int **a, int **b, int size){
    int colorIndex;
    int c[5] = {0, 0, 0, 0, 0};
    int i, j;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            voisin0(c, a, b, i, j, size);
        }
    }
    colorIndex = max_color(c, size);
    return colorIndex;
}