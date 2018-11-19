#include "Node.h"
#include <vector>
#include <queue>
#include<iostream>
using namespace std;



bool une_couleur(vector<vector<int>> a, int size){
    int i, j;
    int t = a[0][0];
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if(a[i][j] != t)
                return false;
        }
    }
    return true;
}

void trouve(vector<vector<int>> a, int x, int y, int c, vector<vector<int>>& b, int n)
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

void propage(queue<pair<Node, vector<int>>>& q, int k)
{
    int i, j;
    int size = q.front().first.size;
    vector<vector<int>> a;
    for(int i = 0; i < size; i++){
        vector<int> vi;
        for(int j = 0; j < size; j++){
            vi.push_back((q.front().first.vv)[i][j]);
        }
        a.push_back(vi);
    }

    vector<int> v = q.front().second;
    /*vector<vector<int>> b = {
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0}
    };*/
    vector<vector<int>> b(6, vector<int>(6, 0));
    b[0][0] = 1;
    trouve(a, 0, 0, a[0][0], b, size);
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++) {
            if (b[i][j] == 1){
                a[i][j] = k;
            }
        }
    }
    v.push_back(k);
    pair<Node, vector<int>> p(Node(size, a), v);
    q.push(p);
}


void solution(queue<pair<Node, vector<int>>>& q){
    while(!q.empty()){
        if(une_couleur(q.front().first.vv, q.front().first.size)){
            for(int ele : q.front().second)
                cout << ele << " ";
            cout << endl;
            return;
        }
        for(int i = 0; i < 4; i++){
            propage(q, i);

        }
        q.pop();
    }
    cout << "no solution" << endl;
}


int main(){
    vector<vector<int>> vv = {
            {0, 0, 1, 2, 1, 3},
            {3, 1, 3, 3, 3, 2},
            {2, 3, 1, 1, 2, 1},
            {2, 2, 3, 3, 1, 0},
            {0, 0, 2, 1, 1, 3},
            {2, 0, 2, 3, 2, 0}
    };

    queue<pair<Node, vector<int>>> q;
    vector<int> vi;
    pair<Node, vector<int>> p(Node(6, vv), vi);
    q.push(p);
    solution(q);
    return 0;
}











