#include<bits/stdc++.h>
using namespace std;
#define reg register

const int len[]={0,1,3,9,27,81,243,729};

int n;
char a[1000][1000];

inline void Solve(reg int n,reg int x,reg int y){
	if(n==1){
		a[x][y]='X';
		return;
	}
	Solve(n-1,x,y);
	Solve(n-1,x-len[n-1],y-len[n-1]);
	Solve(n-1,x-len[n-1],y+len[n-1]);
	Solve(n-1,x+len[n-1],y-len[n-1]);
	Solve(n-1,x+len[n-1],y+len[n-1]);
	return;
}

int main(void){
	memset(a,' ',sizeof(a));
	Solve(7,365,365);
	while(scanf("%d",&n)!=EOF&&n!=-1){
		for(reg int i=1;i<=len[n];++i,putchar('\n'))
			for(reg int j=1;j<=len[n];++j)
				putchar(a[i][j]);
		puts("-");
	}
	return 0;
}
