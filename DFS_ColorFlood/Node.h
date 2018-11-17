#ifndef NODE_H
#define NODE_H

#include<cstring>
#include<vector>
#include<iostream>
using namespace std;

struct Node{
    int size;
    vector<vector<int>> vv;
    Node(int s,vector<vector<int>> v){
        size = s;
        for(int i = 0; i < s; i++){
            vector<int> vi;
            for(int j = 0; j < s; j++){
                vi.push_back(v[i][j]);
            }
            vv.push_back(vi);
        }
    }
};

#endif