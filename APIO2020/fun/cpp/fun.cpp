#include "fun.h"

#include <vector>

#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=500+5;

int dis[MAXN][MAXN];
bool tag[MAXN];

std::vector<int> createFunTour(int N, int Q) {
	int Max=0,l=0,r=0;
	for(reg int i=0;i<N;++i)
		for(reg int j=i+1;j<N;++j){
			dis[i][j]=dis[j][i]=hoursRequired(i,j);
			if(Max<dis[i][j]){
				Max=dis[i][j];
				l=i,r=j;
			}
		}
	reg int tmp=N-1;
	vector<int> V;
	int u=l;
	tag[u]=true;
	V.push_back(u);
	while(tmp--){
		int Max=0,pos=0;
		for(reg int i=0;i<N;++i)
			if(!tag[i]&&u!=i&&Max<dis[u][i]){
				Max=dis[u][i];
				pos=i;
			}
		u=pos;
		tag[u]=true;
		V.push_back(u);
	}
	return V;
}
