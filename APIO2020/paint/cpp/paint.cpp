#include "paint.h"

#include <vector>
#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=1e5+5;
const int MAXM=5e4+5;
const int MAXK=1e5+5;

int dp[MAXN];
int f[MAXK];
int bus[MAXK];

int minimumInstructions(int N, int M, int K, std::vector<int> C,std::vector<int> A, std::vector<std::vector<int>> B) {
	int Max=0;
	for(reg int i=0;i<N;++i){
		++f[C[i]];
		Max=max(Max,f[C[i]]);
	}
	if(Max<=1){
		for(reg int i=0;i<M;++i){
			for(reg int j=0;j<A[i];++j){
				bus[B[i][j]]=i;
			}
		}
	}
	else{
		memset(dp,0x3f,sizeof(dp));
		dp[0]=0;
		for(reg int i=M;i<=N;++i){
			reg bool flag=false;
			reg int y=i-M+1;
			//printf("i=%d flag=%d\n",i,flag);
			for(reg int x=0;x<M&&!flag;++x){
				reg bool f=true;
				for(reg int l=0;l<M;++l){
					reg int id=(x+l)%M,col=C[y+l-1];
					reg bool check=false;
					for(reg int pos=0;pos<A[id];++pos)
						if(B[id][pos]==col){
							check=true;
							break;
						}
					
					if(!check){
						//printf("x=%d y=%d l=%d id=%d col=%d\n",x,y,l,id,col);
						f=false;
						break;
					}
				}
				//printf("x=%d,f=%d\n",x,f);
				if(f)
					flag=true;
			}
			//printf("i=%d flag=%d\n",i,flag);
			if(flag){
				dp[i]=min(dp[i],dp[y-1]+1);
				for(reg int j=y-1;j<=i;++j)
					dp[i]=min(dp[i],dp[j]+1);
			}
		}
		//for(reg int i=0;i<=N;++i)
		//	printf("%d%c",dp[i],i==N?'\n':' ');
		if(dp[N]==0x3f3f3f3f)
			return -1;
		else
			return dp[N];
	}
}